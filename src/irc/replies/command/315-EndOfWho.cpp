#include <irc/replies/CommandReplies.hpp>

namespace irc
{
// 315     IRC_RPL_ENDOFWHO
//             "<name> :End of /WHO list"
	EndOfWhoReply::EndOfWhoReply(std::string const& serverName, std::string const &mask)
		: NumericReply(serverName, IRC_RPL_ENDOFWHO)
	{
		message << mask << " :End of /WHO list";
	}
}
