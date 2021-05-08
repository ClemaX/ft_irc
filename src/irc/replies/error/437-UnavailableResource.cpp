#include <irc/replies/ErrorReplies.hpp>

namespace irc
{
// 437     IRC_ERR_UNAVAILRESOURCE
//             "<nick/channel> :Nick/channel is temporarily unavailable"
	UnavailableResourceError::UnavailableResourceError(std::string const& serverName, std::string const &nickname,
			std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_UNAVAILRESOURCE)
	{
		message << nickname << "/" << channelName << " :Nick/channel is temporarily unavailable";
	}
}
