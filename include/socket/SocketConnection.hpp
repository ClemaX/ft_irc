#pragma once

#include <string> // using std::string

#include <socket/socketdef.hpp> // using socketAddress

#include <socket/SocketExceptions.hpp>

std::ostream &operator<<(std::ostream &os, internetAddress const& addr);

class	SocketConnection
{
public:
	typedef	socketAddress	address;

private:
	int		fd;
	address	socketAddress;

public:
	SocketConnection() throw();

	SocketConnection(int fd, address const& socketAddress);

	virtual	~SocketConnection() throw();

	inline bool	isOpen() const throw()									// definition autorisée dans le header ?
	{ return fd > 0; }

	void	close() throw(SocketCloseException);

	bool	read(char *buffer, size_t n) throw(SocketReadException);

	virtual SocketConnection const&	operator<<(std::string const& str) const
		throw(SocketWriteException);

	inline internetAddress	getAddr() const throw()
	{ return socketAddress.sin6_addr; }

	inline internetPort		getPort() const throw()
	{ return socketAddress.sin6_port; }
};
