# include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
	PassMissMatchError
	::PassMissMatchError(const std::string& serverName)
	: NumericReply(serverName, IRC_ERR_PASSWDMISMATCH, ":Password incorrect")
	{ }
}
