#include <socket/SocketServer.hpp>
#include <socket/SecureSocketConnection.hpp>

#include <fcntl.h>

#include <utils/Logger.hpp>

void	SocketServer::addConnection(int fd,
	SocketConnection* connection)
{
	if (fd != listener.getFd() && fd)
		fdConnectionMap[fd] = connection;

	if (fd > highestFd)
		highestFd = fd;
}

void	SocketServer::removeConnection(int fd)
{
	if (fd > 0)
	{
		delete fdConnectionMap[fd];
		fdConnectionMap.erase(fd);
		if (fd == highestFd)
		{
			if (fdConnectionMap.empty())
				highestFd = sslListener.getFd();
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
	socketAddress const& address, SSL* sslConnection)
{
	SocketConnection*	connection;

	if (sslConnection != NULL)
		connection = new SecureSocketConnection(sslConnection, connectionFd, address);

	else
		connection = new SocketConnection(connectionFd, address);

	Logger::instance() << Logger::INFO << "New connection: "
		<< std::endl << "\tfd: " << connectionFd
		<< std::endl << "\tip: " << address.sin6_addr
		<< std::endl << "\tport: " << address.sin6_port
		<< std::endl << "\tsecure: " << (sslConnection != NULL)
		<< std::endl;

	return (connection);
}

void	SocketServer::onDisconnection(connection* connection)
{
	Logger::instance() << Logger::INFO << "Socket disconnected: "
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

	Logger::instance() << Logger::INFO << "Received message: "
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
		bool isOpen;
		try {
			isOpen = fdConnectionMap[connectionFd]->read(buffer, sizeof(buffer) - 1);
		}
		catch(SocketReadException const& e)
		{
			Logger::instance() << Logger::WARNING << e.what() << ": " << e.why() << std::endl;
			isOpen = false;
		}

		if (isOpen)
			onMessage(fdConnectionMap[connectionFd], buffer);
		else
		{
			onDisconnection(fdConnectionMap[connectionFd]);
			disconnectedFds.push(connectionFd);
		}
	}
}

SocketServer::SocketServer(
	std::string const& hostname, std::string const& port,
	std::string const& sslPort, std::string const& sslCert,
	std::string const& sslKey, unsigned maxClients)
		throw(SocketException)
	:	context(sslCert, sslKey),
		hostname(hostname),
		port(port),
		sslPort(sslPort),
		maxClients(maxClients)
{
	FD_ZERO(&connectionSet);
}

SocketServer::SocketServer()
	:	context(),
		hostname("::"),
		port("2525"),
		maxClients(10)
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
	socketAddress	clientAddr;
	int				incomingFd;

	if (listener.isListening() || sslListener.isListening())
		throw ServerRunningException();

	// Bind
	listener.bind(hostname, port);

	if (!sslPort.empty())
		sslListener.bind(hostname, sslPort);

	// Listen
	listener.listen();
	Logger::instance() << Logger::INFO << "Listening on " << hostname << ":" << port << "..." << std::endl;

	if (sslListener.isOpen())
	{
		sslListener.listen();
		Logger::instance() << Logger::INFO << "Listening on " << hostname << ":" << sslPort << "..." << std::endl;

		highestFd = sslListener.getFd();
	}
	else
		highestFd = listener.getFd();

	// Check for incoming connections
	int	activity;

	while (true)
	{
		FD_ZERO(&connectionSet);
		FD_SET(listener.getFd(), &connectionSet);
		FD_SET(sslListener.getFd(), &connectionSet);

		for (connectionMap::const_iterator it = fdConnectionMap.begin();
			it != fdConnectionMap.end(); ++it)
			FD_SET(it->first, &connectionSet);

		// Wait for incoming data
		activity = select(highestFd + 1, &connectionSet, NULL, NULL, NULL);

		if (activity < 0)
		{
			if (errno == EINTR)
				break;
			int	err = errno; stop(); throw SocketSelectException(err);
		}

		// Accept incoming connections
		if (listener.isInSet(connectionSet))
		{
			Logger::instance() << Logger::DEBUG << "Connection incoming..." << std::endl;

			incomingFd = listener.accept(clientAddr);

			if (incomingFd >= 0)
				addConnection(incomingFd, onConnection(incomingFd, clientAddr));
		}

		// Accept incoming secure connections
		if (sslListener.isInSet(connectionSet))
		{
			Logger::instance() << Logger::DEBUG << "Secure connection incoming..." << std::endl;

			incomingFd = sslListener.accept(clientAddr);

			if (incomingFd >= 0)
				addConnection(incomingFd, onConnection(incomingFd, clientAddr, context.newConnection()));
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
	if (listener.isOpen() || sslListener.isOpen())
	{
		Logger::instance() << Logger::INFO << "Stopping server!" << std::endl;

		onFlush();
		clearConnections();
		try {
			listener.close();
			sslListener.close();
		} catch (SocketCloseException const& e) {
			Logger::instance() << Logger::ERROR  << e.what() << ": " << e.why() << std::endl;
		}

		while (!disconnectedFds.empty())
			disconnectedFds.pop();
	}
}
