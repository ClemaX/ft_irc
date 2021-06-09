#include <socket/SocketServer.hpp>
#include <socket/SecureSocketConnection.hpp>

#include <fcntl.h>

#include <utils/Logger.hpp>

void	SocketServer::addConnection(int fd,
	connection* connection)
{
	if (connection != NULL)
	{
		fdConnectionMap[fd] = connection;
		if (fd > highestFd)
			highestFd = fd;
		Logger::instance() << Logger::DEBUG << "Adding connection on fd " << fd << std::endl;
	}
	else
	{
		Logger::instance() << Logger::DEBUG << "Dropping connection on fd " << fd << std::endl;
		close(fd);
	}
}

void	SocketServer::removeConnection(int fd)
{
	if (fd > 0)
	{
		Logger::instance() << Logger::DEBUG << "Removing connection on fd " << fd << std::endl;
		delete fdConnectionMap[fd];
		fdConnectionMap.erase(fd);
		if (fd == highestFd)
		{
			// This should be updated if there is a possibility that no listener is listening
			if (fdConnectionMap.empty())
			{
				if (sslListener.isListening() && sslListener.getFd() > listener.getFd())
					highestFd = sslListener.getFd();
				else
					highestFd = listener.getFd();
			}
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
	SocketConnection*	connection = NULL;

	try {
		if (sslConnection != NULL)
			connection = new SecureSocketConnection(sslConnection, connectionFd, address);
		else
			connection = new SocketConnection(connectionFd, address);
	} catch (SocketException const& e)
	{ Logger::instance() << Logger::ERROR << e.what() << ": " << e.why() << std::endl; };

	if (connection)
	{
		Logger::instance() << Logger::INFO
			<< "New connection: " << std::endl
			<< "\tfd: " << connectionFd << std::endl
			<< "\tip: " << address.sin6_addr << std::endl
			<< "\tport: " << address.sin6_port << std::endl
			<< "\tsecure: " << (sslConnection != NULL) << std::endl;
	}

	return (connection);
}

void	SocketServer::onDisconnection(connection* connection)
{
	Logger::instance() << Logger::INFO << "Socket disconnected: "
		<< "\tfd: " << connection->getFd() << std::endl
		<< "\tip: " << connection->getAddr() << std::endl
		<< "\tport: " << connection->getPort() << std::endl;
}

void	SocketServer::onMessage(connection* connection,
	std::string const& message)
{
	Logger::instance() << Logger::INFO << "Received message: "
		<< "\tip: " << connection->getAddr() << std::endl
		<< "\tport: " << connection->getPort() << std::endl
		<< "\t'" << message << "'" << std::endl;
}

void	SocketServer::onFlush() const
{
	// Flush messages
	for (connectionMap::const_iterator it = fdConnectionMap.begin(); it != fdConnectionMap.end(); ++it)
		it->second->flush();
}

void	SocketServer::checkActivity(int connectionFd)
{
	if (FD_ISSET(connectionFd, &readFds))
	{
		bool isOpen;
		try {
			isOpen = fdConnectionMap[connectionFd]->read(buffer, sizeof(buffer) - 1);
		}
		catch(SocketReadException const& e)
		{
			Logger::instance() << Logger::WARNING << e.what() << ": " << e.why() << std::endl;
			isOpen = false;
		} // TODO: Maybe close the socket here?

		if (isOpen)
			onMessage(fdConnectionMap[connectionFd], buffer);
		else
		{
			Logger::instance() << Logger::DEBUG << "Adding " << connectionFd << " to disconnected queue..." << std::endl;
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
	FD_ZERO(&readFds);
}

SocketServer::SocketServer()
	:	context(),
		hostname("::"),
		port("2525"),
		maxClients(10)
{
	FD_ZERO(&readFds);
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
		// Clear fd_set
		FD_ZERO(&readFds);

		// Add listeners to fd_set
		if (listener.isListening())
			FD_SET(listener.getFd(), &readFds);
		if (sslListener.isListening())
			FD_SET(sslListener.getFd(), &readFds);

		// Add current connections to fd_set
		for (connectionMap::const_iterator it = fdConnectionMap.begin();
			it != fdConnectionMap.end(); ++it)
			FD_SET(it->first, &readFds);

		// Wait for incoming data
		Logger::instance() << Logger::DEBUG << "Waiting for activity..." << std::endl;
		activity = select(highestFd + 1, &readFds, NULL, NULL, NULL);

		if (activity < 0)
		{
			Logger::instance() << Logger::DEBUG << "Select was interrupted!" << std::endl;
			if (errno == EINTR)
				break;
			int	err = errno; stop(); throw SocketSelectException(err);
		}

		// Accept incoming connections
		if (listener.isInSet(readFds))
		{
			Logger::instance() << Logger::DEBUG << "Connection incoming..." << std::endl;

			incomingFd = listener.accept(clientAddr);

			if (incomingFd >= 0)
				addConnection(incomingFd, onConnection(incomingFd, clientAddr));
		}

		// Accept incoming secure connections
		if (sslListener.isInSet(readFds))
		{
			Logger::instance() << Logger::DEBUG << "Secure connection incoming..." << std::endl;

			incomingFd = sslListener.accept(clientAddr);

			if (incomingFd >= 0)
				addConnection(incomingFd, onConnection(incomingFd, clientAddr, context.newConnection()));
		}

		// Read messages
		Logger::instance() << Logger::DEBUG << "Checking for incoming messages!" << std::endl;
		for (connectionMap::iterator it = fdConnectionMap.begin();
			it != fdConnectionMap.end(); ++it)
			checkActivity(it->first);

		// Remove disconnected sockets
		Logger::instance() << Logger::DEBUG << "Removing queued disconnected connections!" << std::endl;
		while (!disconnectedFds.empty())
		{
			onDisconnection(fdConnectionMap[disconnectedFds.front()]);
			removeConnection(disconnectedFds.front());
			disconnectedFds.pop();
		}

		// Flush connections
		Logger::instance() << Logger::DEBUG << "Flushing connections!" << std::endl;
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
