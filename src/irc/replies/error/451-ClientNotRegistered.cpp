#include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
	ClientNotResgisteredYet::ClientNotResgisteredYet(const std::string& servername)
	: NumericReply(servername, ERR_NOTREGISTRED)
	{ message << ":You have not registered"; }
}
