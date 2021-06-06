#pragma once

#include <socket/SocketExceptions.hpp>
#include <sys/select.h>

class	Socket
{
protected:
	int		fd;

public:
	Socket() throw();

	Socket(int fd);

	virtual	~Socket() throw();

	virtual void	close() throw(SocketCloseException);

	bool	isOpen() const throw()
	{ return fd > 0; }

	int	getFd() const throw()
	{ return fd; }

	bool isInSet(fd_set const& connectionSet) const throw()
	{ return FD_ISSET(fd, &connectionSet); }
};
