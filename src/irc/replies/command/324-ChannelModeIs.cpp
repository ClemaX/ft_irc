#include <irc/replies/CommandReplies.hpp>

namespace irc
{
// 324     IRC_RPL_CHANNELMODEIS
//             "<channel> <mode> <mode params>"
	ChannelModeIsReply::ChannelModeIsReply(std::string const& serverName, std::string const &channelName,
							std::string const &mode, std::string const &modeParams)
		: NumericReply(serverName, IRC_RPL_CHANNELMODEIS)
	{
		message << channelName << " " << mode;
		if (!modeParams.compare(""))
			message << " " << modeParams;
	}
}
