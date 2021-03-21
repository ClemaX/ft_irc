#include <IRCCommand.hpp>

namespace irc
{
	IRCCommand::IRCCommand(std::string const& name)
		:	name(name)
	{ }

	IRCChannelCommand::IRCChannelCommand(std::string const& name,
		bool isOperatorCommand)
		:	IRCCommand(name), isOperatorCommand(isOperatorCommand)
	{ }
}
