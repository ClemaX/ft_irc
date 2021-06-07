#include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
// 332     IRC_RPL_TOPIC
//             "<channel> :<topic>"
	TopicReply::TopicReply(std::string const& serverName, std::string const &channelName,
							std::string const &topic)
		: NumericReply(serverName, IRC_RPL_TOPIC)
	{
		// (void)serverName;
		// message << std::string("TOPIC") + IRC_MESSAGE_DELIM + channelName + IRC_MESSAGE_DELIM + IRC_MESSAGE_PREFIX_PREFIX + topic;
		message << channelName + IRC_MESSAGE_DELIM + topic;
	}
}
