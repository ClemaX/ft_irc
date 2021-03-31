#include <SocketServer.hpp>
#include <fcntl.h>

void	SocketServer::addConnection(int connectionFd,
	SocketConnection* connection)
{
	if (connectionFd != listenFd)
		fdConnectionMap[connectionFd] = connection;		// possible d'ajouter un element dans une map de cette facon ?

	if (connectionFd > highestFd)
		highestFd = connectionFd;
}

void	SocketServer::removeConnection(int connectionFd)
{
	if (connectionFd > 0)
	{
		delete fdConnectionMap[connectionFd];
		fdConnectionMap.erase(connectionFd);
		if (connectionFd == highestFd)
		{
			if (fdConnectionMap.empty())
				highestFd = listenFd;
			else
				highestFd = fdConnectionMap.rbegin()->first;
		}
	}
}

void	SocketServer::clearConnections()
{
	for (connectionMap::const_iterator it = fdConnectionMap.begin();
		it != fdConnectionMap.end(); ++it)
			delete(it->second);
	fdConnectionMap.clear();
}

SocketConnection*	SocketServer::onConnection(int connectionFd,
	struct sockaddr_in const& address)
{
	SocketConnection*	connection = new SocketConnection(connectionFd, address);

	std::cout << "New connection: "
		<< "fd: " << connectionFd
		<< ", ip: " << address.sin_addr.s_addr
		<< ", port: " << address.sin_port
		<< std::endl;

	return (connection);
}

void	SocketServer::onDisconnection(connection* connection)
{
	std::cout << "Socket disconnected: "
		<< ", ip: " << connection->getAddr()
		<< ", port: " << connection->getPort()
		<< std::endl;
}

void	SocketServer::onMessage(connection* connection,
	std::string const& message)
{
	std::cout << "Received message: "
		<< ", ip: " << connection->getAddr()
		<< ", port: " << connection->getPort()
		<< '\'' << message << '\'' << std::endl;
}

void	SocketServer::checkActivity(int connectionFd)
{
	if (FD_ISSET(connectionFd, &connectionSet))
	{
		bool isOpen
			= fdConnectionMap[connectionFd]->read(buffer, sizeof(buffer) - 1);

		if (isOpen)
			onMessage(fdConnectionMap[connectionFd], buffer);
		else
		{
			onDisconnection(fdConnectionMap[connectionFd]);
			disconnectedFds.push(connectionFd);
		}
	}
}

SocketServer::SocketServer(unsigned portNumber, unsigned maxClients)
	:	portNumber(portNumber), maxClients(maxClients),
		listenFd(0), highestFd(0)
{
	FD_ZERO(&connectionSet);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(portNumber);
}

SocketServer::SocketServer()
	:	portNumber(2525),
		maxClients(10),
		listenFd(0),
		highestFd(0)
{
	FD_ZERO(&connectionSet);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(portNumber);
}

SocketServer::~SocketServer()
{ stop(); }

#ifndef SOCK_NONBLOCK
# define SOCK_NONBLOCK 0
#endif

void	SocketServer::start()
{
	int	opt = 1;

	if (listenFd > 0)
		throw ServerException();

	// Open a new socket
	listenFd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

	#if SOCK_NONBLOCK == 0
		fcntl(listenFd, F_SETFL, O_NONBLOCK);
	#endif

	if (listenFd < 0)
	{
		std::cerr << "socket: " << strerror(errno) << std::endl;
		throw SocketOpenException(errno);
	}

	// Allow multiple concurrent connections
	if(setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&opt), sizeof(opt)) < 0 )
	{
		int err = errno;
		std::cerr << "setsockopt: " << strerror(err) << std::endl;
		stop();
		throw SocketOptionException(err);
	}

	// Bind the socket to the server address
	if (bind(listenFd, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr)) < 0)
	{
		int err = errno;
		std::cerr << "bind: " << strerror(err) << std::endl;
		stop();
		throw SocketBindException(err);
	}

	// Listen for new connections
	if (listen(listenFd, 10) < 0)
	{
		int err = errno;
		std::cerr << "listen: " << strerror(errno) << std::endl;
		stop();
		throw SocketListenException(err);
	}
	std::cout << "Listening on port " << portNumber << "..." << std::endl;

	// Add listening socket to connections
	FD_SET(listenFd, &connectionSet);
	highestFd = listenFd;

	// Check for incoming connections
	int					activity;
	struct sockaddr_in	clientAddr;
	socklen_t			addrLen = sizeof(clientAddr);

	while (true)
	{
		FD_ZERO(&connectionSet);
		FD_SET(listenFd, &connectionSet);
		for (connectionMap::const_iterator it = fdConnectionMap.begin();
			it != fdConnectionMap.end(); ++it)
			FD_SET(it->first, &connectionSet);

		// Wait for incoming data
		activity = select(highestFd + 1, &connectionSet, NULL, NULL, NULL);

		if ((activity < 0))
		{
			if (errno == EINTR)
				break;
			int	err = errno;
			std::cerr << "select: " << strerror(err) << std::endl;
			stop();
			throw SocketSelectException(err);
		}

		// Accept incoming connections
		if (FD_ISSET(listenFd, &connectionSet))
		{
			int	incomingFd;

			incomingFd = accept(listenFd,
				reinterpret_cast<struct sockaddr*>(&clientAddr),
				&addrLen);

			if (incomingFd < 0)
			{
				int	err = errno;
				if (err != EWOULDBLOCK) // TODO: Maybe check EAGAIN (man errno)
				{
					stop();
					throw SocketAcceptException(err);
				}
			}

			addConnection(incomingFd, onConnection(incomingFd, clientAddr));
		}

		// Read messages
		for (connectionMap::iterator it = fdConnectionMap.begin();
			it != fdConnectionMap.end(); ++it)
			checkActivity(it->first);

		// Remove disconnected sockets
		for (size_t i = 0; i < disconnectedFds.size(); ++i)
		{
			removeConnection(disconnectedFds.front());
			disconnectedFds.pop();
		}
	}
	stop();
}

void	SocketServer::stop() throw()
{
	if (listenFd > 0)
	{
		std::cout << "Stopping server!" << std::endl;
		clearConnections();
		close(listenFd);
		listenFd = 0;
		for (size_t i = 0; i < disconnectedFds.size(); ++i)
			disconnectedFds.pop();
	}
}
