#include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
// 472     IRC_ERR_UNKNOWNMODE
//             "<char> :is unknown mode char to me"
	UnkownModeError::UnkownModeError(std::string const& serverName,
		std::string const& character)
		:	NumericReply(serverName, IRC_ERR_UNKNOWNMODE)
	{
		message << character << " :is unknown mode char to me";
	}
}
