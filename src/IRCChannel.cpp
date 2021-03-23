#include <IRCChannel.hpp>

namespace irc
{
	ChannelClient::ChannelClient(Client* client, bool isOp)
		:	client(client), isChannelOperator(isOp)
	{ }

	ChannelClient::ChannelClient(Client* client)
		:	client(client), isChannelOperator(false)
	{ }

	Channel::Channel(std::string const& name)
		:	name(name)
	{ }
}
