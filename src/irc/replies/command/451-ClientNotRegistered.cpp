#include <irc/replies/ErrorReplies.hpp>

namespace irc
{
	ClientNotResgisteredYet::ClientNotResgisteredYet(const std::string& servername)
	: NumericReply(servername, ERR_NOTREGISTRED)
	{ message << ":You have not registered"; }
}
