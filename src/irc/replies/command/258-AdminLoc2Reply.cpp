# include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
	AdminLoc2Reply::
	AdminLoc2Reply(const std::string& serverName, const std::string& admin_info)
	: NumericReply(serverName, IRC_RPL_ADMINLOC2, std::string(":") + admin_info)
	{ }
}


