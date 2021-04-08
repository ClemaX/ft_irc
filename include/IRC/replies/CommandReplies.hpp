#pragma once

#include <irc/replies/NumericReplies.hpp>

namespace irc
{
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
