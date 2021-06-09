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

	std::string	writeBuffer;

public:
	std::string	readBuffer;

	SocketConnection() throw();

	SocketConnection(int fd, address const& socketAddress);

	virtual	~SocketConnection() throw();

	/// returns false when socket closed
	virtual bool	read(char* buffer, size_t n) throw(SocketCloseException, SocketReadException);
	virtual bool	write(char const* buffer, size_t n) const
		throw(SocketWriteException);

	/// Add a message to the write buffer.
	/// The messages need to be flushed by calling flush().
	SocketConnection& operator<<(std::string const& message)
	{ writeBuffer += message; return *this; }

	/// Flushes the write buffer.
	void	flush()
	{
		if (write(writeBuffer.c_str(), writeBuffer.length()))
			writeBuffer.clear();
	}

	inline internetAddress	getAddr() const throw()
	{ return addr.sin6_addr; }

	inline internetPort		getPort() const throw()
	{ return addr.sin6_port; }
};
