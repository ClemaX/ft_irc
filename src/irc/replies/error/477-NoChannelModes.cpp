#include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
// 477		IRC_ERR_NOCHANMODES
//             	"<channel> :Channel doesn't support modes"
	NoChanModesError::NoChanModesError(std::string const& serverName,
		std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_NOCHANMODES)
	{
		message << channelName << " :Channel doesn't support modes";
	}
}
