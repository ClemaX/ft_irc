#pragma once

#include <string> // using std::string

#include <socket/socketdef.hpp> // using socketAddress
#include <socket/IConnection.hpp> // using IConnection
#include <socket/Socket.hpp> // using Socket


#include <utils/Logger.hpp>

#include <netdb.h>

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

	SocketConnection() throw()
		:	Socket(), addr()
	{ Logger::instance() << Logger::DEBUG << "Constructing empty SocketConnection..." << std::endl; }

	SocketConnection(int fd, address const& socketAddress)
		:	Socket(fd), addr(socketAddress)
	{ Logger::instance() << Logger::DEBUG << "Constructing SocketConnection on fd " << fd << "..." << std::endl; }

	virtual	~SocketConnection() throw()
	{ Logger::instance() << Logger::DEBUG << "Destroying SocketConnection..." << std::endl; }

	/// returns false when socket close
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

	internetAddress const&	getAddr() const throw()
	{ return addr.sin6_addr; }

	socklen_t				getAddrLen() const throw()
	{ return addr.sin6_len; }

	std::string				getHostname() const
	{ 
		hostent const*const	entry = gethostbyaddr(&getAddr(), getAddrLen(), AF_INET6);

		return std::string((entry && entry->h_name) ? entry->h_name : "");
	}

	internetPort	getPort() const throw()
	{ return addr.sin6_port; }

	bool			hasBufferedData() const throw()
	{ return !writeBuffer.empty(); }
};
