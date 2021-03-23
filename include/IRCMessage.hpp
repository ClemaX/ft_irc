#pragma once

#include <parseField.hpp>

#include <IRCCommand.hpp>

namespace irc
{
	struct	Message
	{
		class	MessageException		:	public std::exception { };

		class	InvalidMessageException	:	public MessageException
		{
			public: char const*	what() const throw()
			{ return "Invalid IRC message"; };
		};

		class	IncompleteMessageException	:	public MessageException
		{
			public: char const*	what() const throw()
			{ return "Incomplete IRC message"; };
		};

		struct	Prefix
		{
			/// Server or nick name.
			std::string	name;
			/// User name.
			std::string	user;
			/// Host name.
			std::string	host;

			Prefix();

			Prefix(std::string const& name,
				std::string const& user = "", std::string const host = "")
				:	name(name), user(user), host(host)
			{ }

			Prefix(std::string::const_iterator& it,
				std::string::const_iterator last) throw(InvalidMessageException);

			inline bool	isEmpty() const throw()
			{ return !(name.length() || user.length() || host.length()); }

			std::string	serialize() const throw()
			{
				std::string	serialized;

				if (!isEmpty())
				{
					serialized.push_back(IRC_MESSAGE_PREFIX_PREFIX);
					serialized.append(name);

					if (user.length())
					{
						serialized.push_back(IRC_MESSAGE_PREFIX_USER_PREFIX);
						serialized.append(user);
					}

					if (host.length())
					{
						serialized.push_back(IRC_MESSAGE_PREFIX_HOST_PREFIX);
						serialized.append(host);
					}
				}

				return serialized;
			}
		};

		Prefix						prefix;
		Command const*			command;
		std::vector<std::string>	arguments;

		Message(std::string& buffer) throw(MessageException);
	};
}
