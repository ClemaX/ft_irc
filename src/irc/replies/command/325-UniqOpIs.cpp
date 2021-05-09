#include <irc/replies/CommandReplies.hpp>

namespace irc
{
// 325     IRC_RPL_UNIQOPIS
//             "<channel> <nickname>"
	UniqOpIsReply::UniqOpIsReply(std::string const& serverName, std::string const &channelName,
							std::string const &nickName)
		: NumericReply(serverName, IRC_RPL_UNIQOPIS)
	{
		message << channelName << " " << nickName;
	}
}
