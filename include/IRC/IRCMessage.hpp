#pragma once

#include <string> // using std::string
#include <vector> // using std::vector

#include <parseField.hpp>

#include <IRCAMessage.hpp>
#include <IRCServer.hpp>

namespace irc
{
	struct	Message	:	AMessage
	{
		Server::Command const*		command;
		std::vector<std::string>	arguments;

		Message(std::string& buffer) throw(MessageException);
	};
}
