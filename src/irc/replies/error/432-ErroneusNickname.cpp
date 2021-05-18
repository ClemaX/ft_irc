#include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
	ErroneusNicknameReply::ErroneusNicknameReply(const std::string& servername,
	const std::string& given_nick)
	: NumericReply(servername, ERR_ERRONEUSNICKNAME, given_nick + " :Erroneous nickname")
	{ }
}
