#include <irc/replies/CommandReplies.hpp>

namespace irc
{

// 301     IRC_RPL_AWAY
//             "<nick> :<away message>"
	AwayReply::AwayReply(std::string const& serverName, std::string const &nickName,
							std::string const &awayMessage)
		: NumericReply(serverName, IRC_RPL_AWAY)
	{
		message << nickName << " :" << awayMessage;
	}
}

