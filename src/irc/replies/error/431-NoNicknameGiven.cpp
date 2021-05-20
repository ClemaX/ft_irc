#include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
	NoNicknameGivenReply::NoNicknameGivenReply(const std::string& servername)
	: NumericReply(servername, ERR_NONICKNAMEGIVEN, ":No nickname given")
	{ }
}
