#include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
// 473     IRC_ERR_INVITEONLYCHAN
//             "<channel> :Cannot join channel (+i)"
	InviteOnlyChanError::InviteOnlyChanError(std::string const& serverName,
		std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_INVITEONLYCHAN)
	{
		message << channelName << " :Cannot join channel (+i)";
	}
}
