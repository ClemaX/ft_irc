#include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
// 367     IRC_RPL_BANLIST
//             "<channel> <banid>"
	BanListReply::BanListReply(std::string const& serverName, std::string const &channelName,
							std::string const &sign, std::string const &banid)
		: NumericReply(serverName, IRC_RPL_BANLIST)
	{
		message << channelName << " " << sign << " " << banid;
	}
}
