#pragma once

#include <iostream> // using std::cout, std::cerr, std::endl
#include <exception> // using std::exception
#include <cstring> // using strerror
#include <cerrno> // using errno
#include <map>
#include <algorithm>

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

	class	SocketOptionException	:	public	SocketException
	{
	public:
		SocketOptionException(int err)	:	SocketException(err) { }

		virtual char const*	what() const throw()
		{ return "Could not set socket option"; }
	};

	class	SocketBindException	:	public	SocketException
	{
	public:
		SocketBindException(int err)	:	SocketException(err) { }

		virtual char const*	what() const throw()
		{ return "Could not bind socket"; }
	};

	class	SocketListenException	:	public	SocketException
	{
	public:
		SocketListenException(int err)	:	SocketException(err) { }

		virtual char const*	what() const throw()
		{ return "Could not listen on socket"; }
	};

	class	SocketSelectException	:	public	SocketException
	{
	public:
		SocketSelectException(int err)	:	SocketException(err) { }

		virtual char const*	what() const throw()
		{ return "Could not select socket connections"; }
	};

	class	SocketAcceptException	:	public	SocketException
	{
	public:
		SocketAcceptException(int err)	:	SocketException(err) { }

		virtual char const*	what() const throw()
		{ return "Could not accept socket connection"; }
	};

	class	SocketReadException	:	public	SocketException
	{
	public:
		SocketReadException(int err)	:	SocketException(err) { }

		virtual char const*	what() const throw()
		{ return "Could not read from socket"; }
	};

	class	SocketServer
	{
	protected:
		typedef	::std::map<int, struct sockaddr_in>		connectionMap;
		typedef	::std::pair<int, struct sockaddr_in>	connectionPair;

		unsigned			portNumber;
		unsigned			maxClients;
		fd_set				connections;
		connectionMap		connectionFds;

		struct sockaddr_in	serverAddr;
		int					listenFd;
		int					highestFd;
		char				buffer[SOCKET_BUFFER_SIZE + 1];

		void	addConnection(int connectionFd, struct sockaddr_in const& address);
		void	removeConnection(int connectionFd);
		void	clearConnections();

		virtual void	onConnection(int connectionFd,
			struct sockaddr_in const& address);
		virtual void	onDisconnection(int connectionFd);
		virtual void	onMessage(int connectionFd, std::string const& message);
		void			checkActivity(connectionPair const& connection);

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
