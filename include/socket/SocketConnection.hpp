#pragma once

#include <string> // using std::string

#include <socket/socketdef.hpp> // using socketAddress
#include <socket/IConnection.hpp> // using IConnection
#include <socket/Socket.hpp> // using Socket

std::ostream &operator<<(std::ostream &os, internetAddress const& addr);

class	SocketConnection	:	public virtual IConnection, public Socket
{
public:
	typedef	socketAddress	address;

protected:
	address	addr;

public:
	SocketConnection() throw();

	SocketConnection(int fd, address const& socketAddress);

	virtual	~SocketConnection() throw();

	/// returns false when socket closed
	virtual bool	read(char* buffer, size_t n) throw(SocketCloseException, SocketReadException);
	virtual bool	write(char const* buffer, size_t n) const
		throw(SocketWriteException);

	virtual SocketConnection const&	operator<<(std::string const& str) const
		throw(SocketWriteException);

	inline internetAddress	getAddr() const throw()
	{ return addr.sin6_addr; }

	inline internetPort		getPort() const throw()
	{ return addr.sin6_port; }
};
