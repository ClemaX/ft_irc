#include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
// 322     IRC_RPL_LIST
//             "<channel> <# visible> :<topic>"
	ListReply::ListReply(std::string const& serverName, std::string const &channelName,
							int numberOfUsers, std::string const &topic)
		: NumericReply(serverName, IRC_RPL_LIST)
	{
		message << channelName;
		if (numberOfUsers)
			message << " " << ft::itoa(numberOfUsers);
		if (topic.compare(""))
			message << " " << topic;
	}
}
