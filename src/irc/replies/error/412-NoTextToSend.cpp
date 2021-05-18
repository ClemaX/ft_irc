#include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
// 412     IRC_ERR_NOTEXTTOSEND
//             ":No text to send"
	NoTextToSendError::NoTextToSendError(std::string const& serverName)
		:	NumericReply(serverName, IRC_ERR_NOTEXTTOSEND)
	{
		message << " :No text to send";
	}
}
