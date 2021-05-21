# include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
	AdminEmailReply::
	AdminEmailReply(const std::string& serverName, const std::string& email)
	:NumericReply(serverName, IRC_RPL_ADMINEMAIL, std::string(":") + email)
	{ }
}
