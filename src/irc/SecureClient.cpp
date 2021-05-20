#include <irc/SecureClient.hpp>

#include <utils/Logger.hpp>

namespace irc
{
	SecureClient::SecureClient(SSL* sslConnection, int fd, socketAddress const& address, bool authRequired)
		:	SocketConnection(fd, address),
			SecureSocketConnection(sslConnection, fd, address),
			Client(fd, address, authRequired)
	{ Logger::instance() << Logger::DEBUG << "Constructing SecureClient on fd " << fd << "..." << std::endl; }
}
