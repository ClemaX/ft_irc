#include <socket/SocketServer.hpp>
#include <fcntl.h>

#include <utils/bindAddress.hpp>

void	SocketServer::addConnection(int connectionFd,
	SocketConnection* connection)
{
	if (connectionFd != listenFd)
		fdConnectionMap[connectionFd] = connection;

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
	socketAddress const& address)
{
	SocketConnection*	connection = new SocketConnection(connectionFd, address);

	std::cout << "New connection: "
		<< "\n\tfd: " << connectionFd
		<< "\n\tip: " << address.sin6_addr
		<< "\n\tport: " << address.sin6_port
		<< std::endl;

	return (connection);
}

void	SocketServer::onDisconnection(connection* connection)
{
	std::cout << "Socket disconnected: "
		<< "\n\tip: " << connection->getAddr()
		<< "\n\tport: " << connection->getPort()
		<< std::endl;
}

void	SocketServer::onMessage(connection* connection,
	std::string const& message)
{
	// std::cout << "Received message: "
	// 	<< "ip: " << connection->getAddr()
	// 	<< ", port: " << connection->getPort()
	// 	<< '\'' << message << '\'' << std::endl;

	std::cout << "Received message: "
		<< "\n\tip: " << connection->getAddr()
		<< "\n\tport: " << connection->getPort()
		<< "\n\t\'" << message << "\'" << std::endl;
}

void	SocketServer::onFlush() const
{ }

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

SocketServer::SocketServer(std::string const& hostname, std::string const &port, unsigned maxClients)
	:	hostname(hostname), port(port), maxClients(maxClients),
		listenFd(0), highestFd(0)
{
	if (this->hostname == "")
		this->hostname = "::";
	if (this->maxClients == 0)
		this->maxClients = 10;

	FD_ZERO(&connectionSet);
}

SocketServer::SocketServer()
	:	hostname("::"),
		port("2525"),
		maxClients(10),
		listenFd(0),
		highestFd(0)
{
	FD_ZERO(&connectionSet);
}

SocketServer::~SocketServer()
{ stop(); }

#ifndef SOCK_NONBLOCK
# define SOCK_NONBLOCK 0
#endif

void	SocketServer::start() throw(ServerException, SocketException)
{
	int	opt = 1;

	if (listenFd > 0)
		throw ServerException();

	// Bind address
	listenFd = bindAddress(hostname, port, SOCK_STREAM, SOCK_NONBLOCK, IPPROTO_IP);

	if (listenFd < 0)
		throw SocketOpenException(errno);

	#if SOCK_NONBLOCK == 0
		fcntl(listenFd, F_SETFL, O_NONBLOCK);
	#endif

	// Allow multiple concurrent connections
	if(setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR,
		reinterpret_cast<char*>(&opt), sizeof(opt)) < 0 )
	{ int err = errno; stop(); throw SocketOptionException(err); }

	// Listen for new connections
	if (listen(listenFd, 10) < 0)
	{ int err = errno; stop(); throw SocketListenException(err); }

	std::cout << "Listening on " << hostname << ':' << port << "..." << std::endl;

	// Add listening socket to connections
	FD_SET(listenFd, &connectionSet);
	highestFd = listenFd;

	// Check for incoming connections
	int					activity;
	struct sockaddr_in6	clientAddr;
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
			int	err = errno; stop(); throw SocketSelectException(err);
		}

		// Accept incoming connections
		if (FD_ISSET(listenFd, &connectionSet))
		{
			int	incomingFd;

			incomingFd = accept(listenFd, reinterpret_cast<sockaddr*>(&clientAddr), &addrLen);

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
		while (!disconnectedFds.empty())
		{
			removeConnection(disconnectedFds.front());
			disconnectedFds.pop();
		}

		// Flush connections
		onFlush();
	}
	// Stop server
	stop();
}

void	SocketServer::stop() throw()
{
	if (listenFd > 0)
	{
		std::cout << "Stopping server!" << std::endl;
		onFlush();
		clearConnections();
		close(listenFd);
		listenFd = 0;
		while (!disconnectedFds.empty())
			disconnectedFds.pop();
	}
}
