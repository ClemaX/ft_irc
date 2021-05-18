#include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
// 368     IRC_RPL_ENDOFBANLIST
//             "<channel> :End of channel ban list"
	EndOfBanListReply::EndOfBanListReply(std::string const& serverName, std::string const &channelName)
		: NumericReply(serverName, IRC_RPL_ENDOFBANLIST)
	{
		message << channelName << " :End of channel ban list";
	}
}
