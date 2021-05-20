#include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
// 323     IRC_RPL_LISTEND
//             ":End of /LIST"
	EndOfListReply::EndOfListReply(std::string const& serverName)
		: NumericReply(serverName, IRC_RPL_LISTEND)
	{
		message << ":End of /LIST";
	}
}
