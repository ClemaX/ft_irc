#include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
// 003     IRC_RPL_CREATED
//             "This server was created <date>"
	CreatedReply::CreatedReply(const std::string& serverName, const std::string& date)
	: NumericReply(serverName, IRC_RPL_CREATED)
	{ message << "This server was created " << date; }
}
