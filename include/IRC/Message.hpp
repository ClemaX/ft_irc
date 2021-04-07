#pragma once

#include <string> // using std::string
#include <vector> // using std::vector

#include <utils/parseField.hpp>

#include <irc/AMessage.hpp>
#include <irc/Server.hpp>

namespace irc
{
	struct	Message	:	AMessage
	{
		Server::Command const*		command;
		// std::string					str_arguments;
		std::vector<std::string>	arguments;

		Message(std::string& buffer) throw(MessageException);
	};
}
