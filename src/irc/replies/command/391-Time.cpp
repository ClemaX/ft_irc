
# include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
	Time::Time(const std::string& serverName, const std::string& local_time)
	: NumericReply(serverName, IRC_RPL_TIME, std::string(":") + local_time)
	{ }
}

