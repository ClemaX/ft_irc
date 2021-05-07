#pragma once

#include <iostream> // using std::cout, std::cerr, std::endl
#include <cerrno> // using errno
#include <map> // using std::map, std::pair
#include <queue> // using std::queue

#include <sys/select.h> // using select
#include <unistd.h>

#include <socket/SocketConnection.hpp>

class	SocketServer
{
protected:
	typedef	SocketConnection				connection;

	typedef	std::pair<int, connection*>		connectionPair;
	typedef	std::map<int, connection*>		connectionMap;
	typedef	std::queue<int>					connectionQueue;

	std::string			hostname;
	std::string			port;

	unsigned			maxClients;
	fd_set				connectionSet;
	connectionMap		fdConnectionMap;
	connectionQueue		disconnectedFds;

	int					listenFd;
	int					highestFd;
	char				buffer[SOCKET_BUFFER_SIZE + 1];

	void	addConnection(int connectionFd, connection* connection);
	void	removeConnection(int connectionFd);
	void	clearConnections();

	void	checkActivity(int connectionFd);

	void	sendMessage(connection* connection, std::string const& message);

	virtual SocketConnection*	onConnection(int connectionFd,
		connection::address const& address);
	virtual void				onDisconnection(connection* connection);
	virtual void				onMessage(connection* connection,
		std::string const& message);

	virtual void				onFlush() const;

public:
	class	ServerException	:	public std::exception
	{ };

	SocketServer(std::string const& hostname, std::string const& port,
		unsigned maxClients);

	SocketServer();

	virtual ~SocketServer();

	void	start() throw(ServerException, SocketException);
	void	stop() throw();
};
