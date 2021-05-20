#pragma once

#include <irc/AMessage.hpp>

namespace NAMESPACE_IRC
{
	struct	PrivateMessage
	: AMessage
	{
		PrivateMessage(std::string const& serverName,
			std::string const &message = "");
		virtual ~PrivateMessage();

		std::string	serialize() const throw();

		Prefix		prefix;
		std::string	message;
	};


	struct JoinChannelMessage
	: PrivateMessage
	{ JoinChannelMessage(std::string const& nickname, std::string const& channelName); };

	struct LeaveChannelMessage
	: PrivateMessage
	{ LeaveChannelMessage(std::string const& nickname, std::string const& channelName,
		std::string const &leaveMessage); };

	struct InviteChannelMessage
	: PrivateMessage
	{ InviteChannelMessage(std::string const& nickname, std::string const& channelName); };

	/////////////////////////////////////
	// Inlined private message members //
	/////////////////////////////////////

	inline
	PrivateMessage::
	~PrivateMessage()
	{ }

	inline std::string
	PrivateMessage::
	serialize() const
	throw()
	{ return (prefix.serialize() + IRC_MESSAGE_DELIM + message + IRC_MESSAGE_SUFFIX); }

	inline
	JoinChannelMessage::
	JoinChannelMessage(std::string const& nickname, std::string const& channelName)
	: PrivateMessage(nickname)
	{ message << "has joined " << channelName; }

	inline
	InviteChannelMessage::
	InviteChannelMessage(std::string const& nickname, std::string const& channelName)
	: PrivateMessage(nickname)
	{ message << nickname << " invites you to " << channelName; }
}
