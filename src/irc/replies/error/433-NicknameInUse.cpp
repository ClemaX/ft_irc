#include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
	NicknameInUseReply::NicknameInUseReply(const std::string& servername,
	const std::string& given_nick)
	: NumericReply(servername, ERR_NICKNAMEINUSE, given_nick + " :Nickname is already in use")
	{ }
}
