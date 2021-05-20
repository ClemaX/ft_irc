#pragma once

#include <irc/AMessage.hpp>

namespace irc
{
	struct	PrivateMessage: AMessage
	{
		PrivateMessage(std::string const& serverName,
			std::string const &message = "");
		virtual ~PrivateMessage();

		std::string	serialize() const throw();

		Prefix		prefix;
		std::string	message;
	};


	struct JoinChannelMessage: PrivateMessage
	{ JoinChannelMessage(std::string const& nickname, std::string const& channelName); };

	struct LeaveChannelMessage: PrivateMessage
	{ LeaveChannelMessage(std::string const& nickname, std::string const& channelName,
		std::string const &leaveMessage); };

	struct InviteChannelMessage: PrivateMessage
	{ InviteChannelMessage(std::string const& nickname, std::string const& channelName); };
}
