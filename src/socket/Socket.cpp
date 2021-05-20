#include <cerrno>
#include <iostream>

#include <socket/Socket.hpp>
#include <unistd.h>

#include <utils/Logger.hpp>

// TODO: Check if this should really throw and stop execution
void	Socket::close() throw(SocketCloseException)
{
	if (isOpen())
	{
		Logger::instance() << Logger::DEBUG << "Closing Socket on fd " << fd << "..." << std::endl;
		if (::close(fd) == -1)
		{
			fd = 0;
			throw SocketCloseException(errno);
		}
		fd = 0;
	}
}

Socket::Socket() throw()
	:	fd(0)
{ Logger::instance() << Logger::DEBUG << "Constructing empty Socket..." << std::endl; }

Socket::Socket(int fd)
	:	fd(fd)
{ Logger::instance() << Logger::DEBUG << "Constructing Socket on fd " << fd << "..." << std::endl; }

Socket::~Socket() throw()
{
	Logger::instance() << Logger::DEBUG << "Destroying Socket..." << std::endl;
	try { close(); }
	catch (SocketCloseException const& e)
	{
		Logger::instance() << Logger::DEBUG << "Socket::close: " << e.what() << ": "
			<< e.why() << std::endl;
	}
}
