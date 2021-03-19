#include <IRCCommand.hpp>

namespace irc
{
	IRCCommand::IRCCommand(std::string const& name, bool isOperatorCommand)
		:	name(name), isOperatorCommand(isOperatorCommand)
	{ }

	bool	IRCCommand::execute(IRCChannelClient const& user, IRCChannel const& channel,
		std::vector<std::string> const& arguments) const
	{
		std::cout << user.username << '@' << channel.name;
		if (isOperatorCommand)
		{
			if (user.isChannelOperator)
				std::cout << " executes privileged command: "
					<< name << std::endl;
			else
			{
				std::cout << " is not a channel operator!" << std::endl;
				return false;
			}
		}
		else
			std::cout << " executes command: " << name << std::endl;

		if (arguments.size())
		{
			std::cout << "Arguments: ";
			for (std::vector<std::string>::const_iterator it = arguments.begin();
				it != arguments.end(); it++)
				std::cout << *it << ", ";
			std::cout << std::endl;
		}
		return true;
	}

	IRCKickCommand::IRCKickCommand()		:	IRCCommand("KICK", true) { }
	IRCModeCommand::IRCModeCommand()		:	IRCCommand("MODE", true) { }
	IRCInviteCommand::IRCInviteCommand()	:	IRCCommand("INVITE", true) { }
	IRCTopicCommand::IRCTopicCommand()		:	IRCCommand("TOPIC", true) { }

	IRCJoinCommand::IRCJoinCommand()		:	IRCCommand("JOIN", false) { }

	IRCCommand const*	parseCommand(
		std::string::const_iterator& it, std::string::const_iterator last)
	{
		std::string	str;
		unsigned	i = 0;

		it = parseField(str, it, last);

		if (str.length() == 0)
			return NULL;

		while (i < commandCount && str != commands[i].name)
			i++;
		if (i == commandCount)
			return NULL;

		return &commands[i];
	}
}
