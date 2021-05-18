#include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
// 349 IRC_RPL_ENDOFEXCEPTLIST
//             "<channel> :End of channel exception list"
	EndOfExceptionListReply::EndOfExceptionListReply(std::string const& serverName, std::string const &channelName)
		: NumericReply(serverName, IRC_RPL_ENDOFEXCEPTLIST)
	{
		message << channelName << " :End of channel exception list";
	}
}
