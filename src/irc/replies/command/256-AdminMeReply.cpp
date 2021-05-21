# include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
	AdminMeReply::
	AdminMeReply(const std::string& serverName, const std::string& admin_nick)
	: NumericReply(serverName, IRC_RPL_ADMINME,
	std::string(":Administrative info about ") + admin_nick)
	{ }
}
