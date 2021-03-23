#pragma once

#include <string> // using std::string
#include <vector> // using std::vector

#include <itoa.hpp>

#include <ircdef.hpp>

#include <IRCMessage.hpp>
#include <IRCClient.hpp>

namespace irc
{
	struct	IReply
	{
		IReply() { };
		virtual ~IReply() { };

		virtual std::string	serialize() const throw() = 0;
	};


	struct	NumericReply	:	IReply
	{
		typedef	std::vector<Client const*> clientList;
		Message::Prefix		prefix;
		int					code;
		std::string			message;

		NumericReply(std::string const& serverName,
			int code, std::string const& message = "")
			:	prefix(serverName),
				code(code),
				message(message)
		{ }

		virtual ~NumericReply()
		{ }

		std::string	serialize() const throw()
		{
			std::string	serialized;

			serialized.append(prefix.serialize());
			serialized.push_back(IRC_MESSAGE_DELIM);
			serialized.append(ft::itoa(code));
			serialized.push_back(IRC_MESSAGE_DELIM);
			serialized.append(message);
			serialized.append(IRC_MESSAGE_SUFFIX);

			return serialized;
		}
	};

	struct NoneReply	:	NumericReply
	{
		NoneReply(std::string const& serverName)
			: NumericReply(serverName, IRC_RPL_NONE)
		{ }
	};


	struct NeedMoreParamsReply	:	NumericReply
	{
		NeedMoreParamsReply(std::string const& serverName,
			std::string const& commandName)
			:	NumericReply(serverName, IRC_ERR_NEEDMOREPARAMS)
		{
			message.append(commandName).append(": Not enough parameters");
		}
	};

	struct UserhostReply	:	NumericReply
	{
		UserhostReply(std::string const& serverName, clientList users)
			: NumericReply(serverName, IRC_RPL_USERHOST)
		{
			for (clientList::const_iterator it = users.begin(); it != users.end(); ++it)
			{
				std::cout << (*it)->nickname;
			}
		}
	};

	/* struct NoneReply	:	NumericReply
	{
		NoneReply(std::string const& serverName)
			: NumericReply(serverName, IRC_RPL_NONE)
		{ }
	}; */
}
