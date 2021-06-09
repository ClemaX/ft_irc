#include <socket/SocketConnection.hpp>

#include <iostream>
#include <iomanip>

#include <unistd.h>

#include <cerrno>

#include <arpa/inet.h>

#include <utils/Logger.hpp>

std::ostream &operator<<(std::ostream &os, internetAddress const& addr)
{
	char	presentation[256];

	inet_ntop(AF_INET6, &addr, presentation, sizeof(presentation));
	os << presentation;
	return os;
}

bool	SocketConnection::read(char *buffer, size_t n)
	throw(SocketCloseException, SocketReadException)
{
	bool	open = isOpen();
	int		nRead;

	if (open)
	{
		nRead = recv(fd, buffer, n, 0);

		if (nRead == 0) // Socket disconnected
		{
			close();
			open = false;
		}
		else if (nRead < 0) // Read error
		{
			buffer[0] = '\0';
			throw SocketReadException(errno);
		}
		else
			buffer[nRead] = '\0';
	}
	return open;
}

bool	SocketConnection::write(char const* buffer, size_t n) const
	throw(SocketWriteException)
{
	bool	open = isOpen();

	if (open && send(fd, buffer, n, 0) == -1)
		throw SocketWriteException(errno);

	return open;
}
