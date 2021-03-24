#pragma once

#include <string> // using std::string

#include <socketdef.hpp> // using socketAddress

#include <SocketExceptions.hpp>

class	SocketConnection
{
public:
	typedef	socketAddress	address;

private:
	int		fd;
	address	socketAddress;

public:
	SocketConnection() throw();

	SocketConnection(int fd, struct sockaddr_in const& socketAddress);

	virtual	~SocketConnection() throw();

	inline bool	isOpen() const throw()
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
