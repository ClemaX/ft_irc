#include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
// 411     IRC_ERR_NORECIPIENT
//             ":No recipient given (<command>)"
	NoRecipientError::NoRecipientError(std::string const& serverName,
		std::string const& commandName)
		:	NumericReply(serverName, IRC_ERR_NORECIPIENT)
	{
		message << " :No recipient given (" << commandName << ")";
	}
}
