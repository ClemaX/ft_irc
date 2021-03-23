#include <IRCClient.hpp>

namespace irc
{
	Client::Client(int fd, struct sockaddr_in const& address)
		:	SocketConnection(fd, address)
	{ buffer.reserve(IRC_MESSAGE_MAXLEN); }

	Client::~Client() throw()
	{ }
}
