#pragma once

#include <string> // using std::string

#include <ircdef.hpp>

#include <parseField.hpp>

namespace irc
{
	struct	AMessage // TODO: Interface Prefix or make message abstract
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

			Prefix(std::string const& name, std::string const& user = "",
				std::string const host = "");

			Prefix(std::string::const_iterator& it,
				std::string::const_iterator last) throw(InvalidMessageException);

			inline bool	isEmpty() const throw()
			{ return !(name.length() || user.length() || host.length()); }

			std::string	serialize() const throw();
		};

		Prefix	prefix;
	};
}
