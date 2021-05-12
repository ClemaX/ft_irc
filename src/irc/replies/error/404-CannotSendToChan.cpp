#include <irc/replies/ErrorReplies.hpp>

namespace irc
{
// 404     IRC_ERR_CANNOTSENDTOCHAN
//             "<channel name> :Cannot send to channel"
	CannotSendToChanError::CannotSendToChanError(std::string const& serverName,
		std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_CANNOTSENDTOCHAN)
	{
		message << channelName << " :Cannot send to channel";
	}
}
