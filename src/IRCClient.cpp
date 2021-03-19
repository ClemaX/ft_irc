#include <IRCClient.hpp>

namespace irc
{
	IRCClient::IRCClient(struct sockaddr_in const& address)
		:	SocketConnection(address)
	{ }
}
