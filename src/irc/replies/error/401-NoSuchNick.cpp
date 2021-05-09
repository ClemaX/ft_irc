#include <irc/replies/ErrorReplies.hpp>

namespace irc
{
// 401     IRC_ERR_NOSUCHNICK
//             "<nickname> :No such nick/channel"
	NoSuchNicknameError::NoSuchNicknameError(std::string const& serverName,
		std::string const& nickname)
		:	NumericReply(serverName, IRC_ERR_NOSUCHNICK)
	{
		message << nickname << " :No such nick/channel";
	}
}
