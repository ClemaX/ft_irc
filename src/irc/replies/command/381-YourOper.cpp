# include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
	YoureOperReply::YoureOperReply(const std::string& serverName)
	: NumericReply(serverName, IRC_RPL_YOUREOPER, ":You are now an IRC operator")
	{ }
}

