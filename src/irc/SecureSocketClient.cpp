#include <irc/SecureSocketClient.hpp>

#include <utils/Logger.hpp>

namespace irc
{
	SecureSocketClient::SecureSocketClient(SSL* sslConnection, int fd, socketAddress const& address, bool authRequired)
		:	SecureSocketConnection(sslConnection, fd, address),
			AClient(authRequired)
	{ Logger::instance() << Logger::DEBUG << "Constructing SecureSocketClient on fd " << fd << "..." << std::endl; }
}
