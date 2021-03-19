#include <SocketServer.hpp>
#include <fcntl.h>

namespace irc
{
	void	SocketServer::addConnection(int connectionFd, struct sockaddr_in const& address)
	{
		if (connectionFd > 0)
		{
			if (connectionFd != listenFd)
				connectionFds[connectionFd] = address;

			if (connectionFd > highestFd)
				highestFd = connectionFd;
		}
	}

	void	SocketServer::removeConnection(int connectionFd)
	{
		if (connectionFd > 0)
		{
			connectionFds.erase(connectionFd);
			if (connectionFd == highestFd)
			{
				if (connectionFds.empty())
					highestFd = listenFd;
				else
					highestFd = connectionFds.rbegin()->first;
			}
			close(connectionFd);
		}
	}

	void	SocketServer::clearConnections()
	{
		for (connectionMap::const_iterator it = connectionFds.begin();
			it != connectionFds.end(); ++it)
			close(it->first);
		connectionFds.clear();
	}

	void	SocketServer::onConnection(int connectionFd, struct sockaddr_in const& address)
	{
		std::cout << "New connection: "
			<< "fd: " << connectionFd
			<< ", ip: " << address.sin_addr.s_addr
			<< ", port: " << address.sin_port
			<< std::endl;
	}

	void	SocketServer::onDisconnection(int connectionFd)
	{
		std::cout << "Socket disconnected: "
			<< "fd: " << connectionFd
			<< ", ip: " << connectionFds[connectionFd].sin_addr.s_addr
			<< ", port: " << connectionFds[connectionFd].sin_port
			<< std::endl;
	}

	void	SocketServer::onMessage(int connectionFd, std::string const& message)
	{
		std::cout << "Received message on fd " << connectionFd << ": "
			<< '\'' << message << '\'' << std::endl;
	}

	void	SocketServer::checkActivity(
		std::pair<int, struct sockaddr_in> const& connection)
	{
		const int	connectionFd = connection.first;

		if (FD_ISSET(connectionFd, &connections))
		{
			int	ret = recv(connectionFd, buffer, sizeof(buffer) - 1, 0);

			if (ret == 0)
			{
				onDisconnection(connectionFd);
				disconnectedFds.push(connectionFd);
			}
			else if (ret < 0)
			{
				int err = errno;
				std::cerr << "read: " << strerror(err) << std::endl;
				throw SocketReadException(err);
			}
			else
			{
				buffer[ret] = '\0';
				onMessage(connectionFd, buffer);
			}
		}
	}

	SocketServer::SocketServer(unsigned portNumber, unsigned maxClients)
		:	portNumber(portNumber), maxClients(maxClients),
			listenFd(0), highestFd(0)
	{
		FD_ZERO(&connections);
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_addr.s_addr = INADDR_ANY;
		serverAddr.sin_port = htons(portNumber);
	}

	SocketServer::SocketServer()
		:	portNumber(1337), maxClients(10), listenFd(0), highestFd(0)
	{
		FD_ZERO(&connections);
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_addr.s_addr = INADDR_ANY;
		serverAddr.sin_port = htons(portNumber);
	}

	SocketServer::~SocketServer()
	{ stop(); }

	void	SocketServer::start()
	{
		int	opt = 1;

		if (listenFd > 0)
			throw ServerException();

		// Open a new socket
		listenFd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

		if (listenFd < 0)
		{
			std::cerr << "socket: " << strerror(errno) << std::endl;
			throw SocketOpenException(errno);
		}

		// Allow multiple concurrent connections
		if(setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
		{
			int err = errno;
			std::cerr << "setsockopt: " << strerror(err) << std::endl;
			stop();
			throw SocketOptionException(err);
		}

		// Bind the socket to the server address
		if (bind(listenFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
		{
			int err = errno;
			std::cerr << "binding: " << strerror(err) << std::endl;
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
		FD_SET(listenFd, &connections);
		highestFd = listenFd;

		// Check for incoming connections
		int					activity;
		struct sockaddr_in	clientAddr;
		socklen_t			addrLen = sizeof(clientAddr);

		while (true)
		{
			FD_ZERO(&connections);
			FD_SET(listenFd, &connections);
			for (connectionMap::const_iterator it = connectionFds.begin();
				it != connectionFds.end(); ++it)
				FD_SET(it->first, &connections);

			// Wait for incoming data
			activity = select(highestFd + 1, &connections, NULL, NULL, NULL);

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
			if (FD_ISSET(listenFd, &connections))
			{
				int	incomingFd;

				incomingFd = accept(listenFd,
					reinterpret_cast<struct sockaddr*>(&clientAddr),
					&addrLen);

				if (incomingFd < 0)
				{
					int	err = errno;
					if (err != EWOULDBLOCK)
					{
						stop();
						throw SocketAcceptException(err);
					}
				}
				addConnection(incomingFd, clientAddr);
				onConnection(incomingFd, clientAddr);
			}

			// Read messages
			for (connectionMap::iterator it = connectionFds.begin();
				it != connectionFds.end(); ++it)
				checkActivity(*it);

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
}
