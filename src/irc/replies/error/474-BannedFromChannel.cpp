#include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
// 474     IRC_ERR_BANNEDFROMCHAN
//             "<channel> :Cannot join channel (+b)"
	BannedFromChanError::BannedFromChanError(std::string const& serverName,
		std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_BANNEDFROMCHAN)
	{
		message << channelName << " :Cannot join channel (+b)";
	}
}
