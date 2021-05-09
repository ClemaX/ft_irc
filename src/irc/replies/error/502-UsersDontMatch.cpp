#include <irc/replies/ErrorReplies.hpp>

namespace irc
{
// 502     IRC_ERR_USERSDONTMATCH
//             ":Cant change mode for other users"
	UsersDontMatchError::UsersDontMatchError(std::string const& serverName)
		:	NumericReply(serverName, IRC_ERR_USERSDONTMATCH)
	{
		message << ":Cant change mode for other users";
	}
}
