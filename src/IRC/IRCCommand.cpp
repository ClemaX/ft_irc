#include <IRCServer.hpp>

namespace irc
{
	Server::Command::Command(std::string const& name)
		:	name(name)
	{ }

	Server::ChannelCommand::ChannelCommand(std::string const& name,
		bool isOperatorCommand)
		:	Command(name), isOperatorCommand(isOperatorCommand)
	{ }


}
