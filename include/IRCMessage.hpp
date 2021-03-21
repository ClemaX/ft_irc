#pragma once

#include <parseField.hpp>

#include <IRCCommand.hpp>
#include <IRCServer.hpp>

namespace irc
{
	struct	IRCMessage
	{
		class	IRCMessageException		:	public std::exception { };

		class	InvalidMessageException	:	public IRCMessageException
		{
			public: char const*	what() const throw()
			{ return "Invalid IRC message"; };
		};

		struct	Prefix
		{
			std::string	name;
			std::string	user;
			std::string	host;

			Prefix();

			Prefix(std::string::const_iterator& it,
				std::string::const_iterator last);
		};

		Prefix						prefix;
		IRCCommand const*			command;
		std::vector<std::string>	arguments;

		/// CR-LF should be stripped of message string!
		IRCMessage(std::string message);
	};
}
