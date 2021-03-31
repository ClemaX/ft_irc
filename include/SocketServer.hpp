#pragma once

#include <iostream> // using std::cout, std::cerr, std::endl
#include <cerrno> // using errno
#include <map> // using std::map, std::pair
#include <queue> // using std::queue

#include <sys/select.h> // using select
#include <unistd.h>

#include <SocketConnection.hpp>

class	SocketServer
{
protected:
	typedef	SocketConnection				connection;

	typedef	std::pair<int, connection*>		connectionPair;
	typedef	std::map<int, connection*>		connectionMap;
	typedef	std::queue<int>					connectionQueue;

	unsigned			portNumber;
	unsigned			maxClients;
	fd_set				connections;		// qu'est vraiment fd_set ?
	connectionMap		connectionFds;
	connectionQueue		disconnectedFds;

	connection::address	serverAddr;
	int					listenFd;
	int					highestFd;
	char				buffer[SOCKET_BUFFER_SIZE + 1];

	void	addConnection(int connectionFd, connection* connection);
	void	removeConnection(int connectionFd);
	void	clearConnections();

	void	checkActivity(int connectionFd);

	void	sendMessage(connection* connection, std::string const& message);

	virtual SocketConnection	*onConnection(int connectionFd,
		connection::address const& address);
	virtual void				onDisconnection(connection* connection);
	virtual void				onMessage(connection* connection,
		std::string const& message);

public:
	class	ServerException	:	public std::exception
	{ };

	SocketServer(unsigned portNumber, unsigned maxClients);

	SocketServer();

	virtual ~SocketServer();

	void	start();
	void	stop() throw();
};
