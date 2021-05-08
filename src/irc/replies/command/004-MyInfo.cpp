#include <irc/replies/CommandReplies.hpp>

namespace irc
{
// 004     IRC_RPL_MYINFO
//             "<servername> <version> <available user modes> <available channel modes>"
	MyInfoReply::MyInfoReply(const std::string& serverName, const std::string& version,
	const std::string& umodes, const std::string& chmodes)
	: NumericReply(serverName, IRC_RPL_MYINFO)
	{ std::cout << serverName << " " << version << " " << umodes << " " << chmodes << std::endl; }
}
