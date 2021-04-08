#pragma once

#include <irc/AMessage.hpp>

namespace irc
{
	struct	IReply	:	AMessage
	{
		IReply() { };
		virtual ~IReply() { };

		virtual std::string	serialize() const throw() = 0;
	};
}
