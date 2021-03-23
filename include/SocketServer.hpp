#pragma once

#include <iostream> // using std::cout, std::cerr, std::endl
#include <cerrno> // using errno
#include <map> // using std::map, std::pair
#include <queue> // using std::queue

#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <unistd.h>

#include <SocketExceptions.hpp>

#ifndef SOCKET_BUFFER_SIZE
# define SOCKET_BUFFER_SIZE	513U
#endif

typedef	sockaddr_in	socketAddress;
typedef	in_addr_t	internetAddress;
typedef	in_port_t	internetPort;

class	SocketConnection
{
private:
	int				fd;
	socketAddress	socketAddress;

public:
	SocketConnection() throw();

	SocketConnection(int fd, struct sockaddr_in const& socketAddress);

	virtual	~SocketConnection() throw();

	bool	isOpen() const throw()
	{ return fd > 0; }

	void	close() throw(SocketCloseException);

	bool	read(char *buffer, size_t n) throw(SocketReadException);

	virtual SocketConnection const&	operator<<(std::string const& str) const
		throw(SocketWriteException);

	inline internetAddress	getAddr() const throw()
	{ return socketAddress.sin_addr.s_addr; }

	inline internetPort		getPort() const throw()
	{ return socketAddress.sin_port; }
};

class	SocketServer
{
protected:
	typedef	SocketConnection				connection;
	typedef	struct sockaddr_in				connectionAddress;
	typedef	::std::pair<int, connection*>	connectionPair;
	typedef	::std::map<int, connection*>	connectionMap;
	typedef	::std::queue<int>				connectionQueue;

	unsigned			portNumber;
	unsigned			maxClients;
	fd_set				connections;
	connectionMap		connectionFds;
	connectionQueue		disconnectedFds;

	connectionAddress	serverAddr;
	int					listenFd;
	int					highestFd;
	char				buffer[SOCKET_BUFFER_SIZE + 1];

	void	addConnection(int connectionFd, connection* connection);
	void	removeConnection(int connectionFd);
	void	clearConnections();

	void	checkActivity(int connectionFd);

	void	sendMessage(connection* connection, std::string const& message);

	virtual SocketConnection	*onConnection(int connectionFd,
		connectionAddress const& address);
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
