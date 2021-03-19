#include <IRCChannel.hpp>

namespace irc
{
	IRCChannelClient::IRCChannelClient(struct sockaddr_in const& address)
		:	IRCClient(address), isChannelOperator(false)
	{ }

	IRCChannel::IRCChannel(std::string const& name)
		:	name(name)
	{ }
}
