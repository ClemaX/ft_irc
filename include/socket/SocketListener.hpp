#pragma once

#include <string> // using std::string

#include <socket/socketdef.hpp>
#include <socket/Socket.hpp> // using Socket

class SocketListener	:	public Socket
{
protected:
	bool	listening;

public:
	SocketListener() throw();
	~SocketListener() throw();

	SocketListener(std::string const& hostname, std::string const& service,
		int type = SOCK_STREAM, int opt = SOCK_NONBLOCK, int proto = IPPROTO_IP)
		throw(SocketOpenException, SocketBindException, SocketOptionException);

	void			bind(std::string const& hostname, std::string const& service,
		int type = SOCK_STREAM, int opt = SOCK_NONBLOCK, int proto = IPPROTO_IP)
		throw(SocketCloseException, SocketOpenException, SocketBindException, SocketOptionException);

	void			listen() throw(SocketListenException);

	virtual int		accept(socketAddress& clientAddr) const;

	virtual void	close() throw(SocketCloseException);

	bool	isListening() const throw()
	{ return listening; }
};

