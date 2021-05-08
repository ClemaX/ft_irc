#include <irc/replies/ErrorReplies.hpp>

namespace irc
{
// 441     IRC_ERR_USERNOTINCHANNEL
//             "<nick> <channel> :They aren't on that channel"
	UserNotInChannelError::UserNotInChannelError(std::string const& serverName, std::string const &nickname,
			std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_USERNOTINCHANNEL)
	{
		message << nickname << " " << channelName << " :They aren't on that channel";
	}
}
