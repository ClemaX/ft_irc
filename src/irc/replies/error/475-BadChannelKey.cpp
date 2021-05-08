#include <irc/replies/ErrorReplies.hpp>

namespace irc
{
// 475     IRC_ERR_BADCHANNELKEY
//             "<channel> :Cannot join channel (+k)"
	BadChannelKeyError::BadChannelKeyError(std::string const& serverName,
		std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_BADCHANNELKEY)
	{
		message << channelName << " :Cannot join channel (+k)";
	}
}
