#include <irc/replies/CommandReplies.hpp>

namespace irc
{
// 366     IRC_RPL_ENDOFNAMES
//             "<channel> :End of /NAMES list"
	EndOfNamesReply::EndOfNamesReply(std::string const& serverName, std::string const &channelName)
		: NumericReply(serverName, IRC_RPL_ENDOFNAMES)
	{
		message << channelName << " :End of /NAMES list";
	}
}
