#include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
	NickCollisionReply::NickCollisionReply(const std::string& servername,
	const std::string& given_nick, const std::string& username, const std::string& hostname)
	: NumericReply(servername, ERR_NICKCOLLISION, given_nick + " :Nickname collision KILL from "
	+ username + "@" + hostname)
	{ }
}
