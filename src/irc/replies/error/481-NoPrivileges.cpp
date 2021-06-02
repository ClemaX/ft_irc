# include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
	NoprivilegesError::NoprivilegesError(const std::string& serverName)
	: NumericReply(serverName, IRC_ERR_NOPRIVILEGES, ":Permission Denied- You're not an IRC operator")
	{ }
}
