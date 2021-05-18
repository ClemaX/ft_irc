#include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
// 482     IRC_ERR_CHANOPRIVSNEEDED
//             "<channel> :You're not channel operator"
	ChannelOperatorPrivilegiesError::ChannelOperatorPrivilegiesError(std::string const& serverName, std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_CHANOPRIVSNEEDED)
	{
		message << channelName << " :You're not channel operator";
	}
}
