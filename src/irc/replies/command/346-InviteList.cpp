#include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
// 346 IRC_RPL_INVITELIST
//             "<channel> <invitemask>"
	InviteListReply::InviteListReply(std::string const& serverName, std::string const &channelName,
							std::string const &sign, std::string const &inviteMask)
		: NumericReply(serverName, IRC_RPL_INVITELIST)
	{
		message << channelName << " " << sign << " " << inviteMask;
	}
}
