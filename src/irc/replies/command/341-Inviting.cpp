#include <irc/replies/CommandReplies.hpp>

namespace irc
{
// 341     IRC_RPL_INVITING
//             "<channel> <nick>"
	InvitingReply::InvitingReply(std::string const& serverName, std::string const &channelName,
							std::string const &nickname)
		: NumericReply(serverName, IRC_RPL_INVITING)
	{
		message << nickname << " has been invited to join " << channelName;
	}
}
