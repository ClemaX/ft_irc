#pragma once

#include <iostream> // using std::cout, std::cerr, std::endl
#include <exception> // using std::exception
#include <cstring> // using strerror
#include <cerrno> // using errno
#include <map> // using std::map
#include <queue> // using std::queue
//#include <algorithm>

#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <unistd.h>

#ifndef SOCKET_BUFFER_SIZE
# define SOCKET_BUFFER_SIZE	512U
#endif

namespace irc
{
	class	SocketException	:	public ::std::exception
	{
	protected:
		const int	err;
		char const*	errMeaning;

	public:
		SocketException(int err)
			:	err(err), errMeaning(strerror(err))
		{ }

		char const*	why() const throw()
		{ return  errMeaning; }
	};

	class	SocketOpenException	:	public SocketException
	{
	public:
		SocketOpenException(int err)	:	SocketException(err) { }

		virtual char const*	what() const throw()
		{ return "Could not open socket"; };
	};

	class	SocketOptionException	:	public SocketException
	{
	public:
		SocketOptionException(int err)	:	SocketException(err) { }

		virtual char const*	what() const throw()
		{ return "Could not set socket option"; }
	};

	class	SocketBindException	:	public SocketException
	{
	public:
		SocketBindException(int err)	:	SocketException(err) { }

		virtual char const*	what() const throw()
		{ return "Could not bind socket"; }
	};

	class	SocketListenException	:	public SocketException
	{
	public:
		SocketListenException(int err)	:	SocketException(err) { }

		virtual char const*	what() const throw()
		{ return "Could not listen on socket"; }
	};

	class	SocketSelectException	:	public SocketException
	{
	public:
		SocketSelectException(int err)	:	SocketException(err) { }

		virtual char const*	what() const throw()
		{ return "Could not select socket connections"; }
	};

	class	SocketAcceptException	:	public SocketException
	{
	public:
		SocketAcceptException(int err)	:	SocketException(err) { }

		virtual char const*	what() const throw()
		{ return "Could not accept socket connection"; }
	};

	class	SocketReadException	:	public SocketException
	{
	public:
		SocketReadException(int err)	:	SocketException(err) { }

		virtual char const*	what() const throw()
		{ return "Could not read from socket"; }
	};

	struct	SocketConnection
	{
		struct sockaddr_in	address;
		SocketConnection(struct sockaddr_in const& address)
			:	address(address)
		{ }
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

		~SocketServer();

		void	start();
		void	stop() throw();
	};
}
