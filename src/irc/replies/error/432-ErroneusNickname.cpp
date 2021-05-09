#include <irc/replies/ErrorReplies.hpp>

namespace irc
{
	ErroneusNicknameReply::ErroneusNicknameReply(const std::string& servername,
	const std::string& given_nick)
	: NumericReply(servername, ERR_ERRONEUSNICKNAME, given_nick + " :Erroneous nickname")
	{ }
}
