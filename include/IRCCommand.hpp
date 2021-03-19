#pragma once

#include <parseField.hpp>

#include <IRCChannel.hpp>

namespace irc
{
	struct	IRCCommand
	{
		std::string const	name;
		bool const			isOperatorCommand;

		IRCCommand(std::string const& name, bool isOperatorCommand);

		virtual bool	execute(IRCChannelClient const& user, IRCChannel const& channel,
			std::vector<std::string> const& arguments) const;
	};

	struct	IRCKickCommand	:	IRCCommand
	{ IRCKickCommand(); };

	struct	IRCModeCommand	:	IRCCommand
	{ IRCModeCommand(); };

	struct	IRCInviteCommand	:	IRCCommand
	{ IRCInviteCommand(); };

	struct	IRCTopicCommand	:	IRCCommand
	{ IRCTopicCommand(); };


	struct	IRCJoinCommand	:	IRCCommand
	{ IRCJoinCommand(); };

	static IRCCommand const	commands[] =
	{
		IRCJoinCommand(),
		IRCKickCommand(),
		IRCModeCommand(),
		IRCInviteCommand(),
		IRCTopicCommand()
	};

	static unsigned const	commandCount = sizeof(commands) / sizeof(*commands);

	IRCCommand const*	parseCommand(std::string::const_iterator& it,
		std::string::const_iterator last);
}
