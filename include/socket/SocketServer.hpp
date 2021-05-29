#pragma once

#include <iostream> // using std::cout, std::cerr, std::endl
#include <cerrno> // using errno
#include <map> // using std::map, std::pair
#include <queue> // using std::queue

#include <sys/select.h> // using select
#include <unistd.h> // using NULL

#include <socket/ssl.hpp> // using ssl::Context
#include <socket/SocketConnection.hpp>
#include <socket/SocketListener.hpp>


class	SocketServer
{
private:
	void			acceptConnection(int fd, SSL* secure = NULL);

protected:
	typedef	SocketConnection				connection;

	typedef	std::pair<int, connection*>		connectionPair;
	typedef	std::map<int, connection*>		connectionMap;
	typedef	std::queue<int>					connectionQueue;

	ssl::Context		context;

	std::string			hostname;
	std::string			port;
	std::string			sslPort;

	unsigned			maxClients;
	fd_set				connectionSet;
	connectionMap		fdConnectionMap;
	connectionQueue		disconnectedFds;

	SocketListener		listener;
	SocketListener		sslListener;

	int					highestFd;
	char				buffer[SOCKET_BUFFER_SIZE + 1];

	void	addConnection(int connectionFd, connection* connection);
	void	removeConnection(int connectionFd);
	void	clearConnections();

	void	checkActivity(int connectionFd);

	void	sendMessage(connection* connection, std::string const& message);

	virtual connection*		onConnection(int connectionFd, SocketConnection::address const& address, SSL* sslConnection = NULL);
	virtual void				onDisconnection(connection* connection);
	virtual void				onMessage(connection* connection,
		std::string const& message);

	virtual void				onFlush() const;

public:
	class	ServerException	:	public std::exception
	{ };

	class	ServerRunningException	: public ServerException
	{
	public:
		virtual char const* what() const throw()
		{ return "Server already running"; };
	};

	SocketServer(std::string const& hostname, std::string const& port,
		std::string const& sslPort, std::string const& certFile,
		std::string const& keyFile, unsigned maxClients)
			throw(SocketException);

	SocketServer();

	virtual ~SocketServer();

	void	start() throw(ServerException, SocketException);
	void	stop() throw();
};
