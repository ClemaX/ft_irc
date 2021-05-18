#pragma once

#include <string> // using std::string

#include <irc/ircdef.hpp>

#include <utils/parseField.hpp>

namespace NAMESPACE_IRC
{
	std::string &	operator<<(std::string &src, std::string const& str);

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

			bool	isEmpty() const throw()
			{ return !(name.length() || user.length() || host.length()); }

			std::string	serialize() const throw();
			unsigned	length() const throw();
		};

		Prefix	prefix;
	};
}
