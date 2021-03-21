#include <IRCClient.hpp>

namespace irc
{
	IRCClient::IRCClient(int fd, struct sockaddr_in const& address)
		:	SocketConnection(fd, address)
	{ }

	IRCClient::~IRCClient() throw()
	{ }
}
