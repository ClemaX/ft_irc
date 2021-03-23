#include <IRCCommand.hpp>

namespace irc
{
	Command::Command(std::string const& name)
		:	name(name)
	{ }

	ChannelCommand::ChannelCommand(std::string const& name,
		bool isOperatorCommand)
		:	Command(name), isOperatorCommand(isOperatorCommand)
	{ }
}
