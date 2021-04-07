#include <SocketServer.hpp>

SocketConnection::SocketConnection() throw()
	:	fd(0), socketAddress()
{ }


SocketConnection::SocketConnection(int fd, struct sockaddr_in const& socketAddress)
	:	fd(fd), socketAddress(socketAddress)
{ }

SocketConnection::~SocketConnection() throw()
{
	try { close(); }
	catch (SocketCloseException const& e)
	{
		std::cerr << "SocketConnection::close: " << e.what() << ": "
			<< e.why() << std::endl;
	}
}

void	SocketConnection::close() throw(SocketCloseException)
{
	if (isOpen() && ::close(fd) == -1)
	{
		fd = 0;
		throw SocketCloseException(errno);
	}
	fd = 0;
}

bool	SocketConnection::read(char *buffer, size_t n) throw(SocketReadException)
{
	bool	success = isOpen();
	int		nRead;

	if (success)
	{
		nRead = recv(fd, buffer, n, 0);

		if (nRead == 0) // Socket disconnected
		{
			close();
			success = false;
		}
		else if (nRead < 0) // Read error
		{
			buffer[0] = '\0';
			throw SocketReadException(errno);
		}
		else
			buffer[nRead] = '\0';
	}
	return success;
}

SocketConnection const&	SocketConnection::operator<<(std::string const& str) const
	throw(SocketWriteException)
{
	if (isOpen() && send(fd, str.c_str(), str.length(), 0) == -1)
		throw SocketWriteException(errno);
	return *this;
}