#include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
// 501     IRC_ERR_UMODEUNKNOWNFLAG
//             ":Unknown MODE flag"
	UModeUnkownFlagError::UModeUnkownFlagError(std::string const& serverName)
		:	NumericReply(serverName, IRC_ERR_UMODEUNKNOWNFLAG)
	{
		message << ":Unknown MODE flag";
	}
}
