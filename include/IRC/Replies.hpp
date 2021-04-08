#pragma once

#include <iostream> // TODO: Remove: using std::cout

#include <string> // using std::string
#include <vector> // using std::vector

#include <utils/itoa.hpp>

#include <irc/ircdef.hpp>

#include <irc/IReply.hpp>

namespace irc
{
	class	Client;

	template<typename Cstart, typename Ccontent, typename Cend>
	std::string	serializeReplyList(std::string const& serverName,
		std::string const& nickName, std::string const& list, char delim = '\n',
		size_t maxLength = 80)
	{
		(void)static_cast<IReply*>((Cstart*)NULL);
		(void)static_cast<IReply*>((Ccontent*)NULL);
		(void)static_cast<IReply*>((Cend*)NULL);

		std::string	message;

		std::string::size_type	pos = 0;
		std::string::size_type	newPos = list.find(delim, pos);

		if (newPos == std::string::npos)
			newPos = list.length();
		if (newPos > pos + maxLength)
			newPos = maxLength;

		message.append(Cstart(serverName, nickName, list.substr(pos, newPos)).serialize());
		while (newPos < list.length())
		{
			pos = newPos + 1;
			newPos = list.find(delim, pos);

			if (newPos == std::string::npos)
				newPos = list.length();
			if (newPos > pos + maxLength)
				newPos = pos + maxLength;

			message.append(Ccontent(serverName, nickName, list.substr(pos, newPos)).serialize());
		}

		message.append(Cend(serverName, nickName).serialize());
		return (message);
	}

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

	struct MotdStartReply	:	NumericReply
	{
		MotdStartReply(std::string const& serverName,
			std::string const& nickName, std::string const& motd)
			throw(InvalidMessageException);
	};

	struct MotdReply		:	NumericReply
	{
		MotdReply(std::string const& serverName, std::string const& nickName,
			std::string const& motd)
			throw(InvalidMessageException);
	};

	struct EndOfMotdReply	:	NumericReply
	{
		EndOfMotdReply(std::string const& serverName,
			std::string const& nickName);
	};
}
