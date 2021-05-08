#include <irc/replies/CommandReplies.hpp>

namespace irc
{

// 331     IRC_RPL_NOTOPIC
//             "<channel> :No topic is set"
	NoTopicReply::NoTopicReply(std::string const& serverName, std::string const &channelName)
		: NumericReply(serverName, IRC_RPL_NOTOPIC)
	{
		message << channelName << " :No topic is set";
	}
}
