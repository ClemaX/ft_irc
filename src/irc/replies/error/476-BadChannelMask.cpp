#include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
// 476		IRC_ERR_BADCHANMASK
//             	"<channel> :Bad Channel Mask"
	BadChanMaskError::BadChanMaskError(std::string const& serverName,
		std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_BADCHANMASK)
	{
		message << channelName << " :Bad Channel Mask";
	}
}
