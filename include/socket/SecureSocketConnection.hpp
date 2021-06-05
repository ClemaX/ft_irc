#pragma once

#include <string> // using std::string

#include <socket/socketdef.hpp> // using socketAddress

#include <socket/SocketConnection.hpp> // using SocketConnection

#include <socket/ssl.hpp> // using SSL

std::ostream &operator<<(std::ostream &os, internetAddress const& addr);

class	SecureSocketConnection	:	public SocketConnection
{
protected:
	SSL		*sslConnection;

public:
	SecureSocketConnection() throw();

	SecureSocketConnection(SSL* sslConnection, int fd,
		address const& socketAddress) throw(SSLAcceptException);

	virtual	~SecureSocketConnection() throw();

	virtual void	close() throw(SocketCloseException);

	/// returns false when socket closed
	virtual bool	read(char* buffer, size_t n) throw(SocketCloseException, SocketReadException);
	virtual bool	write(char const* buffer, size_t n) const
		throw(SocketWriteException);
};
