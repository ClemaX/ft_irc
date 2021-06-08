#include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
// 324     IRC_RPL_CHANNELMODEIS
//             "<channel> <mode> <mode params>"
	ChannelModeIsReply::ChannelModeIsReply(std::string const& prefix, std::string const &channelName, std::string const &mode, std::string const &modeParams)
		: NumericReply(prefix, IRC_RPL_CHANNELMODEIS)
	{
		message << channelName + " " + mode;
		if (!modeParams.empty())
			message << modeParams;
	}
}
