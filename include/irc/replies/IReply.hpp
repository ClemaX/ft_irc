#pragma once

#include <irc/AMessage.hpp>

namespace NAMESPACE_IRC
{
	struct	IReply	:	AMessage
	{
		IReply() { };
		virtual ~IReply() { };

		virtual std::string	serialize() const throw() = 0;
	};
}
