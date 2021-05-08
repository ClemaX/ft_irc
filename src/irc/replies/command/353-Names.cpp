#include <irc/replies/CommandReplies.hpp>
#include <irc/Channel.hpp>

namespace irc
{
// 353     IRC_RPL_NAMREPLY
//             "<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]"
	ChannelNamesReply::ChannelNamesReply(std::string const& serverName, Channel *channel)
		: NumericReply(serverName, IRC_RPL_NAMREPLY)
	{
		message << channel->name << " :";
		for (Channel::channelClientMap::const_iterator it = channel->clientsMap.begin(); it != channel->clientsMap.end(); it++)
		{
			if (channel->isOperator(it->first))
				message << "@";
			else
				message << "+";		// need to be checked
			message << it->first->nickname << " ";
		}
	}
}
