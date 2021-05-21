#include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
	Version::Version(const std::string& serverName, const std::string& version)
	: NumericReply(serverName, IRC_RPL_VERSION, serverName + " is running version " + version)
	{ }
}

