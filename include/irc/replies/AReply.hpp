#pragma once

#include <string> // using std::string
#include <vector> // using std::vector

#include <utils/itoa.hpp>
#include <utils/itoaReply.hpp>

#include <irc/ircdef.hpp>

#include <irc/replies/IReply.hpp>

namespace NAMESPACE_IRC
{
	struct	AReply
	: IReply
	{
		Prefix		prefix;
		int			code;
		std::string	message;

		AReply(std::string const& serverName,
			std::string const& message = std::string());

		virtual ~AReply();

		std::string	serialize(const std::string &nickname) const throw();
	};

	///////////////////////////////////
	// Numeric Reply inlined members //
	///////////////////////////////////

	inline std::string
	AReply::
	serialize(const std::string &nickname) const
	throw()
	{
		static_cast<void>(nickname);
		return (prefix.serialize() + IRC_MESSAGE_DELIM + message + IRC_MESSAGE_SUFFIX);
	}

	inline
	AReply::
	AReply(std::string const& serverName, std::string const& message)
	: prefix(serverName), message(message)
	{ }

	inline
	AReply::~AReply()
	{ }
}
