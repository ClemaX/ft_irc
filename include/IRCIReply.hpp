#pragma once

#include <IRCAMessage.hpp>

namespace irc
{
	struct	IReply	:	AMessage
	{
		IReply() { };
		virtual ~IReply() { };

		virtual std::string	serialize() const throw() = 0;
	};
}
