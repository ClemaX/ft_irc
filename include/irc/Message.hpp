#pragma once

#include <string> // using std::string
#include <vector> // using std::vector

#include <utils/parseField.hpp>

#include <irc/AMessage.hpp>
#include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	struct	Message	:	AMessage
	{
		Server::Command const*		command;
		std::vector<std::string>	arguments;

		Message();
		~Message();

		Message(std::string& buffer) throw(MessageException);
	};
}
