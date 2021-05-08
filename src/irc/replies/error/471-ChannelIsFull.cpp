#include <irc/replies/ErrorReplies.hpp>

namespace irc
{
// 471     IRC_ERR_CHANNELISFULL
//             "<channel> :Cannot join channel (+l)"
	ChannelIsFullError::ChannelIsFullError(std::string const& serverName,
		std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_CHANNELISFULL)
	{
		message << channelName << " :Cannot join channel (+l)";
	}
}
