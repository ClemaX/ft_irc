#include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
/// 005     IRC_RPL_BOUNCE
//             "Try server <server name>, port <port number>"
	BounceReply::BounceReply(const std::string& serverName, const std::string& portNB)
	: NumericReply(serverName, IRC_RPL_BOUNCE)
	{ std::cout << "Try server " << serverName << ", port " << portNB << std::endl; }
}
