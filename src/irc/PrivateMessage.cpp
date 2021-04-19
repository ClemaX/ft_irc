#include <irc/PrivateMessage.hpp>
#include <irc/Client.hpp>

namespace irc
{
	PrivateMessage::PrivateMessage(std::string const& nickname,
		std::string const& message)
		:	prefix(nickname),
			message(message)
	{ }

	PrivateMessage::~PrivateMessage()
	{ }

	std::string	PrivateMessage::serialize() const throw()
	{
		std::string	serialized;

		serialized.append(prefix.serialize());
		serialized.push_back(IRC_MESSAGE_DELIM);
		serialized.append(message);
		serialized.append(IRC_MESSAGE_SUFFIX);

		return serialized;
	}




	JoinChannelMessage::JoinChannelMessage(std::string const& nickname,
		std::string const& channelName)
		: PrivateMessage(nickname)
	{
		message << "has joined " << channelName;
	}

	LeaveChannelMessage::LeaveChannelMessage(std::string const& nickname,
		std::string const& channelName, std::string const &leaveMessage)
		: PrivateMessage(nickname)
	{
		if (leaveMessage.compare(""))
			message << leaveMessage;
		else
			message << "has left " << channelName;
	}

	InviteChannelMessage::InviteChannelMessage(std::string const& nickname,
		std::string const& channelName)
		: PrivateMessage(nickname)
	{
		message << nickname << " invites you to " << channelName;
	}

}
