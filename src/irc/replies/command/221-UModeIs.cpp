#include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
// 221     IRC_RPL_UMODEIS
//             "<user mode string>"
	UModeIsReply::UModeIsReply(std::string const& serverName, std::string const &userMode)
		: NumericReply(serverName, IRC_RPL_UMODEIS)
	{
		message << userMode;
	}
}
