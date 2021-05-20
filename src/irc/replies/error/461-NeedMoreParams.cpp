#include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
// 461     IRC_ERR_NEEDMOREPARAMS
//             "<command> :Not enough parameters"
	NeedMoreParamsError::NeedMoreParamsError(std::string const& serverName,
		std::string const& commandName)
		:	NumericReply(serverName, IRC_ERR_NEEDMOREPARAMS)
	{
		message << commandName << " :Not enough parameters";
	}
}
