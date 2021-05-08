#include <irc/replies/CommandReplies.hpp>

namespace irc
{
// 347 IRC_RPL_ENDOFINVITELIST
//             "<channel> :End of channel invite list"
	EndOfInviteListReply::EndOfInviteListReply(std::string const& serverName, std::string const &channelName)
		: NumericReply(serverName, IRC_RPL_ENDOFINVITELIST)
	{
		message << channelName << " :End of channel invite list";
	}
}
