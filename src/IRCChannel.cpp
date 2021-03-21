#include <IRCChannel.hpp>

namespace irc
{
	IRCChannelClient::IRCChannelClient(IRCClient* client, bool isOp)
		:	client(client), isChannelOperator(isOp)
	{ }

	IRCChannelClient::IRCChannelClient(IRCClient* client)
		:	client(client), isChannelOperator(false)
	{ }

	IRCChannel::IRCChannel(std::string const& name)
		:	name(name)
	{ }
}
