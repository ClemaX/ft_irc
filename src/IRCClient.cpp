#include <IRCClient.hpp>

namespace irc
{
	IRCClient::IRCClient(int fd, struct sockaddr_in const& address)
		:	SocketConnection(fd, address)
	{ buffer.reserve(IRC_MESSAGE_MAXLEN); }

	IRCClient::~IRCClient() throw()
	{ }
}
