#include <irc/replies/ErrorReplies.hpp>

namespace irc
{
// 442     IRC_ERR_NOTONCHANNEL
//             "<channel> :You're not on that channel"
	NotOnChannelError::NotOnChannelError(std::string const& serverName, std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_NOTONCHANNEL)
	{
		message << channelName << " :You're not on that channel";
	}
}
