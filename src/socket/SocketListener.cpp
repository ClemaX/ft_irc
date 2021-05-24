#include <socket/SocketListener.hpp>

#include <socket/socketdef.hpp>
#include <socket/bindAddress.hpp>

#include <iostream>

#include <cerrno>
#include <sys/fcntl.h>

#include <utils/Logger.hpp>

SocketListener::SocketListener() throw()
	:    listening(false)
{ Logger::instance() << Logger::DEBUG << "Constructing empty SocketListener..." << std::endl; }

SocketListener::SocketListener(std::string const& hostname,
	std::string const& service, int type, int opt, int proto)
	throw(SocketBindException, SocketOpenException, SocketOptionException)
	:	Socket(bindAddress(hostname, service, type, opt, proto)),
		listening(false)
{
	if (fd < 0)
		throw SocketOpenException(errno);

	Logger::instance() << Logger::DEBUG << "Constructing SocketListener on fd " << fd << "..." << std::endl;

	// Enable non-blocking io using fcntl if SOCK_NONBLOCK is not supported
#if SOCK_NONBLOCK == 0
	if (opt & SOCK_NONBLOCK)
		fcntl(fd, F_SETFL, O_NONBLOCK);
#endif

	// Allow socket address reuse
	int	reuseSocketOpt = 1;

	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
		reinterpret_cast<char*>(&reuseSocketOpt), sizeof(reuseSocketOpt)) < 0)
	{ int err = errno; close(); throw SocketOptionException(err); };
}

void	SocketListener::bind(std::string const& hostname, std::string const& service,
	int type, int opt, int proto)
	throw(SocketBindException, SocketOpenException, SocketOptionException, SocketCloseException)
{
	if (listening)
		close();

	Logger::instance() << Logger::DEBUG << "Binding address " << hostname << ':' << service << "..." << std::endl;

	fd = bindAddress(hostname, service, type, opt, proto);
}

void	SocketListener::listen()
	throw(SocketListenException)
{
	// Listen
	// TODO: Maybe throw AlreadyListeningException from here
	if (isOpen() && !listening)
	{
		if(::listen(fd, 10) < 0)
		{ int err = errno; close(); throw SocketListenException(err); };

		listening = true;
	}
}

int		SocketListener::accept(socketAddress& clientAddr) const throw(SocketAcceptException)
{
	sockaddr*const	addr = reinterpret_cast<sockaddr*>(&clientAddr);
	socklen_t		addrLen = sizeof(clientAddr);
	const int		incomingFd = ::accept(fd, addr, &addrLen);

	// TODO: Check if it is better to throw here or in Server
	if (incomingFd < 0 && errno != EWOULDBLOCK)
		throw SocketAcceptException(errno);

	return incomingFd;
}

void	SocketListener::close() throw(SocketCloseException)
{
	listening = false;
	Socket::close();
}

SocketListener::~SocketListener() throw()
{
	Logger::instance() << Logger::DEBUG << "Destroying SocketListener..." << std::endl;
}
