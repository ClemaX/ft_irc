#pragma once

#include <irc/replies/AReply.hpp>

namespace NAMESPACE_IRC
{
	struct	PrivateMessage
	: IReply
	{
		PrivateMessage(std::string const& serverName,
			std::string const &message = "");
		virtual ~PrivateMessage();

		std::string	serialize(const std::string &nickname) const throw();

		Prefix		prefix;
		std::string	message;
	};

	struct JoinChannelMessage
	: AReply
	{ JoinChannelMessage(std::string const &servername, std::string const& channelName); };

	struct PrivmsgChannelMessage
	: AReply
	{ PrivmsgChannelMessage(std::string const &servername, std::string const& channelName, std::string const& privateMessage); };

	struct LeaveChannelMessage
	: AReply
	{ LeaveChannelMessage(std::string const &servername, std::string const& channelName,
		std::string const &leaveMessage); };

	struct InviteChannelMessage
	: AReply
	{ InviteChannelMessage(std::string const &servername, std::string const& nickname, std::string const& channelName); };

	/////////////////////////////////////
	// Inlined private message members //
	/////////////////////////////////////

	inline
	PrivateMessage::PrivateMessage(std::string const& nickname,
		std::string const& message)
		:	prefix(nickname),
			message(message)
	{ }

	inline
	PrivateMessage::
	~PrivateMessage()
	{ }

	inline std::string
	PrivateMessage::
	serialize(const std::string &nickname = "") const
	throw()
	{ 
		(void)nickname;
		return (prefix.serialize() + IRC_MESSAGE_DELIM + message + IRC_MESSAGE_SUFFIX); }
		// return (prefix.serialize() + IRC_MESSAGE_DELIM + IRC_MESSAGE_PREFIX_PREFIX + message + IRC_MESSAGE_SUFFIX); }

	inline
	JoinChannelMessage::
	JoinChannelMessage(std::string const &servername, std::string const& channelName)
	: AReply(servername)
	{ message << "JOIN " << channelName; }

	inline
	PrivmsgChannelMessage::
	PrivmsgChannelMessage(std::string const &nickname, std::string const& channelName, std::string const& privateMessage)
	: AReply(nickname)
	{message << std::string("PRIVMSG") + IRC_MESSAGE_DELIM + channelName + IRC_MESSAGE_DELIM + IRC_MESSAGE_PREFIX_PREFIX + privateMessage;}

	inline
	LeaveChannelMessage::LeaveChannelMessage(std::string const &servername, std::string const& channelName,
		std::string const &leaveMessage)
		: AReply(servername)
	{
		if (leaveMessage.compare(""))
			message << leaveMessage;
		else
			message << "has left " << channelName;
	}

	inline
	InviteChannelMessage::
	InviteChannelMessage(std::string const &servername, std::string const& nickname, std::string const& channelName)
	: AReply(servername)
	{ message << nickname << " INVITE " << channelName; }
}
