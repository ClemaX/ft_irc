#include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
// 402     IRC_ERR_NOSUCHSERVER
//             "<server name> :No such server"
	NoSuchServerError::NoSuchServerError(std::string const& serverName)
		:	NumericReply(serverName, IRC_ERR_NOSUCHSERVER)
	{
		message << serverName << " :No such server";
	}
}
