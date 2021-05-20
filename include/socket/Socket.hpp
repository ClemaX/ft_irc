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

	inline bool	isOpen() const throw()									// definition autorisée dans le header ?
	{ return fd > 0; }

	inline int	getFd() const throw()
	{ return fd; }

	inline bool isInSet(fd_set const& connectionSet) const throw()
	{ return FD_ISSET(fd, &connectionSet); }
};
