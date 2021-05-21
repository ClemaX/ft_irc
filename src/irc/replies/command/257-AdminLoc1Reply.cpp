# include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
	AdminLoc1Reply::
	AdminLoc1Reply(const std::string& serverName, const std::string& admin_info)
	: NumericReply(serverName, IRC_RPL_ADMINLOC1, std::string(":") + admin_info)
	{ }
}

