#include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
// 416     IRC_ERR_TOOMANYMATCHES
	TooManyMatchesError::TooManyMatchesError(std::string const& serverName)
		:	NumericReply(serverName, IRC_ERR_TOOMANYMATCHES)
	{
		message << ":Too many matches";
	}
}
