#pragma once

#include <string> // using std::string
#include <vector> // using std::vector

#include <utils/itoa.hpp>
#include <utils/itoaReply.hpp>

#include <irc/ircdef.hpp>

#include <irc/replies/IReply.hpp>

namespace NAMESPACE_IRC
{
	template<typename Cstart, typename Ccontent, typename Cend>
	std::string	serializeReplyList(std::string const& serverName,
		std::string const& nickName, std::string const& list, char delim = '\n',
		size_t maxLength = 80)
	{
		std::string	message;

		std::string::size_type	pos = 0;
		std::string::size_type	newPos = list.find(delim, pos);

		if (newPos == std::string::npos)
			newPos = list.length();
		if (newPos > pos + maxLength)
			newPos = maxLength;

		message.append(Cstart(serverName, nickName, list.substr(pos, newPos)).serialize(nickName));
		while (newPos < list.length())
		{
			pos = newPos + 1;
			newPos = list.find(delim, pos);

			if (newPos == std::string::npos)
				newPos = list.length();
			if (newPos > pos + maxLength)
				newPos = pos + maxLength;

			message.append(Ccontent(serverName, nickName, list.substr(pos, newPos)).serialize(nickName));
		}

		message.append(Cend(serverName, nickName).serialize(nickName));
		return (message);
	}

	struct	NumericReply
	: IReply
	{
		Prefix		prefix;
		int			code;
		std::string	message;

		NumericReply(std::string const& serverName, int code,
			std::string const& message = std::string());

		virtual ~NumericReply();

		std::string	serialize(const std::string &nickname) const throw();
	};

	///////////////////////////////////
	// Numeric Reply inlined members //
	///////////////////////////////////

	inline std::string
	NumericReply::
	serialize(const std::string &nickname) const
	throw()
	{
		return (prefix.serialize() + IRC_MESSAGE_DELIM + ft::itoaReply(code) + IRC_MESSAGE_DELIM + nickname
		+ IRC_MESSAGE_DELIM + message + IRC_MESSAGE_SUFFIX);
	}

	inline
	NumericReply::
	NumericReply(std::string const& serverName, int code, std::string const& message)
	: prefix(serverName), code(code), message(message)
	{ }

	inline
	NumericReply::~NumericReply()
	{ }
}
