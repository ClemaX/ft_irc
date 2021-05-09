#include <irc/replies/ErrorReplies.hpp>

namespace irc
{
// 443     IRC_ERR_USERONCHANNEL
//             "<user> <channel> :is already on channel"
	UserOnChannelError::UserOnChannelError(std::string const& serverName, std::string const& nickname,
			std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_USERONCHANNEL)
	{
		message << nickname << " " << channelName << " :is already on channel";
	}
}
