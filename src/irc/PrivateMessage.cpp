#include <irc/PrivateMessage.hpp>

namespace NAMESPACE_IRC
{
	PrivateMessage::PrivateMessage(std::string const& nickname,
		std::string const& message)
		:	prefix(nickname),
			message(message)
	{ }

	LeaveChannelMessage::LeaveChannelMessage(std::string const& nickname,
		std::string const& channelName, std::string const &leaveMessage)
		: PrivateMessage(nickname)
	{
		if (leaveMessage.compare(""))
			message << leaveMessage;
		else
			message << "has left " << channelName;
	}
}
