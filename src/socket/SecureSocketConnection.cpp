#include <socket/SecureSocketConnection.hpp>

#include <iostream>
#include <iomanip>

#include <unistd.h>

#include <cerrno>

#include <arpa/inet.h>
#include <socket/ssl.hpp>

#include <utils/Logger.hpp>

SecureSocketConnection::SecureSocketConnection() throw()
	:	SocketConnection()
{ Logger::instance() << Logger::DEBUG << "Constructing empty SecureSocketConnection..." << std::endl; }

SecureSocketConnection::SecureSocketConnection(SSL* sslConnection, int fd,
	address const& socketAddress) throw(SSLAcceptException)
	:	SocketConnection(fd, socketAddress),
		sslConnection(sslConnection)
{
	Logger::instance() << Logger::DEBUG << "Constructing SecureSocketConnection on fd " << fd << "..." << std::endl;
	Logger::instance() << Logger::DEBUG << "Accepting SSL connection..." << std::endl;
	SSL_set_fd(sslConnection, fd);

	if (SSL_accept(sslConnection) <= 0)
		throw SSLAcceptException(errno);
}

SecureSocketConnection::~SecureSocketConnection() throw()
{
	Logger::instance() << Logger::DEBUG << "Destroying SecureSocketConnection..." << std::endl;
	// TODO: Check if secure close is called automatically
}

void SecureSocketConnection::close() throw(SocketCloseException)
{
	Logger::instance() << Logger::DEBUG  << "Closing SecureSocketConnection..." << std::endl;
	if (sslConnection != NULL)
	{
		Logger::instance() << Logger::DEBUG << "Closing SSL on fd " << fd << "..." << std::endl;
		SSL_shutdown(sslConnection);
		SSL_free(sslConnection);
		sslConnection = NULL;
	}
	SocketConnection::close();
}

bool	SecureSocketConnection::read(char *buffer, size_t n)
	throw(SocketCloseException, SocketReadException)
{
	bool	open = isOpen();
	int		nRead;

	if (open)
	{
		nRead = SSL_read(sslConnection, buffer, n);

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

bool	SecureSocketConnection::write(char const* buffer, size_t n) const
	throw(SocketWriteException)
{
	bool	open = isOpen();

	if (open && SSL_write(sslConnection, buffer, n) == -1)
		throw SocketWriteException(errno);

	return open;
}
