#pragma once

#include <iostream> // TODO: Remove: using std::cout

#include <string> // using std::string
#include <vector> // using std::vector

#include <itoa.hpp>

#include <ircdef.hpp>

#include <IRCIReply.hpp>

namespace irc
{
	class	Client;

	struct	NumericReply	:	IReply
	{
		typedef	std::vector<Client const*> clientList;

		Prefix		prefix;
		int			code;
		std::string	message;

		NumericReply(std::string const& serverName, int code,
			std::string const& message);

		virtual ~NumericReply();

		std::string	serialize() const throw();
	};

	struct NeedMoreParamsReply	:	NumericReply
	{
		NeedMoreParamsReply(std::string const& serverName,
			std::string const& commandName);
	};

	struct UserhostReply	:	NumericReply
	{ UserhostReply(std::string const& serverName, clientList users); };
}
