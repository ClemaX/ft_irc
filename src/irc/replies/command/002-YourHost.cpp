#include <irc/replies/CommandReplies.hpp>

namespace irc
{
// 002     IRC_RPL_YOURHOST
//             "Your host is <servername>, running version <ver>"
	YourHostReply::YourHostReply(const std::string& serverName, const std::string& versionName)
	: NumericReply(serverName, IRC_RPL_YOURHOST)
	{ message << "Your host is " << serverName << ", running version " << versionName; }
}
