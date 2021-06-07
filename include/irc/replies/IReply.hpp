#pragma once

#include <irc/AMessage.hpp>

namespace NAMESPACE_IRC
{
	struct	IReply	:	AMessage
	{
		IReply() { };
		virtual ~IReply() { };

		virtual std::string	serialize(const std::string &nickname) const throw() = 0;
	};
}
