#pragma once

#include <itoa.hpp>
#include <parseField.hpp>

#include <IRCChannel.hpp>


namespace irc
{
	class	Server;

	struct	Command
	{
		typedef std::vector<std::string>	argumentList;
		std::string const	name;

		Command(std::string const& name);

		virtual bool	execute(Server& server, Client* user,
			argumentList const& arguments) const = 0;
	};

	struct	ChannelCommand	:	public Command
	{
		bool const	isOperatorCommand;

		ChannelCommand(std::string const& name, bool isOperatorCommand);
	};

	Command const*	parseCommand(std::string::const_iterator& it,
		std::string::const_iterator last);
}
