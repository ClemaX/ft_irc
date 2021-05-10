#include <irc/replies/ErrorReplies.hpp>

namespace irc
{
	UserNeedMoreParams::UserNeedMoreParams(const std::string& servername)
	: NumericReply(servername, ERR_NEEDMOREPARAMS)
	{ message << "Not enough parameters"; }
}
