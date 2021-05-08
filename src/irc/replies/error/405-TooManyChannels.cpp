#include <irc/replies/ErrorReplies.hpp>

namespace irc
{
// 405     IRC_ERR_TOOMANYCHANNELS
//             "<channel name> :You have joined too many channels"
	TooManyChannelsError::TooManyChannelsError(std::string const& serverName,
		std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_TOOMANYCHANNELS)
	{
		message << channelName << " :You have joined too many channels";
	}
}
