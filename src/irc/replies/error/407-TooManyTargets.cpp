#include <irc/replies/ErrorReplies.hpp>

namespace irc
{
// 407     IRC_ERR_TOOMANYTARGETS
//             "<target> :Duplicate recipients. No message"
	TooManyTargetError::TooManyTargetError(std::string const& serverName,
		std::string const& targetName)
		:	NumericReply(serverName, IRC_ERR_TOOMANYTARGETS)
	{
		message << targetName << " :Duplicate recipients. No message";
	}
}
