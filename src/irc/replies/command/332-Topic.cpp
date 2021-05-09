#include <irc/replies/CommandReplies.hpp>

namespace irc
{
// 332     IRC_RPL_TOPIC
//             "<channel> :<topic>"
	TopicReply::TopicReply(std::string const& serverName, std::string const &channelName,
							std::string const &topic)
		: NumericReply(serverName, IRC_RPL_TOPIC)
	{
		message << channelName << " :" << topic;
	}
}
