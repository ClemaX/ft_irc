#include <irc/replies/ErrorReplies.hpp>

namespace irc
{
// 403     IRC_ERR_NOSUCHCHANNEL
//             "<channel name> :No such channel"
	NoSuchChannelError::NoSuchChannelError(std::string const& serverName,
		std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_NOSUCHCHANNEL)
	{
		message << channelName << " :No such channel";
	}
}
