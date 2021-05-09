#include <irc/replies/ErrorReplies.hpp>

namespace irc
{
	NoNicknameGivenReply::NoNicknameGivenReply(const std::string& servername)
	: NumericReply(servername, ERR_NONICKNAMEGIVEN, ":No nickname given")
	{ }
}
