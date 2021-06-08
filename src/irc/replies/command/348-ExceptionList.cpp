#include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
// 348 IRC_RPL_EXCEPTLIST
//             "<channel> <exceptionmask>"
	ExceptionListReply::ExceptionListReply(std::string const& serverName, std::string const &channelName,
							std::string const &sign, std::string const &exceptionMask)
		: NumericReply(serverName, IRC_RPL_EXCEPTLIST)
	{
		message << channelName << " " << sign << " " << exceptionMask;
	}
}
