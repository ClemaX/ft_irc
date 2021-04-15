#pragma once

#include <irc/AMessage.hpp>

namespace irc
{
	struct	PrivateMessage: AMessage
	{
		PrivateMessage(std::string const& serverName,
			std::string const &message = "");
		virtual ~PrivateMessage();

		std::string	serialize() const throw();

		Prefix		prefix;
		std::string	message;
	};
}
