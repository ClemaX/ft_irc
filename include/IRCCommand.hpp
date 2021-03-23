#pragma once

#include <itoa.hpp>
#include <parseField.hpp>

#include <IRCChannel.hpp>


namespace irc
{
	class	IRCServer;

	struct	IRCCommand
	{
		typedef std::vector<std::string>	argumentList;
		std::string const	name;

		IRCCommand(std::string const& name);

		virtual bool	execute(IRCServer& server, IRCClient* user,
			argumentList const& arguments) const = 0;
	};

	struct	IRCChannelCommand	:	public IRCCommand
	{
		bool const	isOperatorCommand;

		IRCChannelCommand(std::string const& name, bool isOperatorCommand);
	};

	IRCCommand const*	parseCommand(std::string::const_iterator& it,
		std::string::const_iterator last);
}
