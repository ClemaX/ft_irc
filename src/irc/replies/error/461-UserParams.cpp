#include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
	UserNeedMoreParams::UserNeedMoreParams(const std::string& servername)
	: NumericReply(servername, ERR_NEEDMOREPARAMS)
	{ message << "Not enough parameters"; }
}
