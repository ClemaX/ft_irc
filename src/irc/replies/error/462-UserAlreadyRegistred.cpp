#include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
	UserAlreadyRegistred::UserAlreadyRegistred(const std::string& servername, const std::string& given_nick)
	: NumericReply(servername, ERR_ALREADYREGISTRED, given_nick + " :You may not reregister")
	{ }
}
