#include <IRCServer.hpp>

namespace irc
{
	IRCServer::IRCKickCommand::IRCKickCommand()
		:	IRCChannelCommand("KICK", true)
	{ }

	bool	IRCServer::IRCKickCommand::execute(IRCServer& server, IRCClient const* user,
		argumentList const& arguments) const
	{
		(void)server;
		(void)arguments;
		std::cout << user->username << " executes " << name << std::endl;
		return false;
	}

	IRCServer::IRCModeCommand::IRCModeCommand()
		:	IRCChannelCommand("MODE", true)
	{ }

	bool	IRCServer::IRCModeCommand::execute(IRCServer& server, IRCClient const* user,
		argumentList const& arguments) const
	{
		(void)server;
		(void)arguments;
		std::cout << user->username << " executes " << name << std::endl;
		return false;
	}

	IRCServer::IRCInviteCommand::IRCInviteCommand()
		:	IRCChannelCommand("INVITE", true)
	{ }

	bool	IRCServer::IRCInviteCommand::execute(IRCServer& server, IRCClient const* user,
		argumentList const& arguments) const
	{
		(void)server;
		(void)arguments;
		std::cout << user->username << " executes " << name << std::endl;
		return false;
	}

	IRCServer::IRCTopicCommand::IRCTopicCommand()
		:	IRCChannelCommand("TOPIC", true)
	{ }

	bool	IRCServer::IRCTopicCommand::execute(IRCServer& server, IRCClient const* user,
		argumentList const& arguments) const
	{
		(void)server;
		(void)arguments;
		std::cout << user->username << " executes " << name << std::endl;
		return false;
	}

	IRCServer::IRCPassCommand::IRCPassCommand()
		:	IRCCommand("PASS")
	{ }

	bool	IRCServer::IRCPassCommand::execute(IRCServer& server, IRCClient const* user,
		argumentList const& arguments) const
	{
		(void)server;
		std::cout << user->username << " executes " << name << std::endl;

		if (!arguments.size())
		{
			*user << "NOTENOUGHARGS";
			return false;
		}
		std::cout << "Setting password '" << arguments[0] << "'" << std::endl;
		return true;
	}

	IRCServer::IRCJoinCommand::IRCJoinCommand()
		:	IRCCommand("JOIN")
	{ }

	bool	IRCServer::IRCJoinCommand::execute(IRCServer& server, IRCClient const* user,
		argumentList const& arguments) const
	{
		(void)server;
		std::cout << user->username << " executes " << name << std::endl;

		if (arguments.size())
		{
			std::cout << "Arguments: ";
			for (argumentList::const_iterator it = arguments.begin();
				it != arguments.end(); it++)
				std::cout << *it << ", ";
			std::cout << std::endl;
		}
		return false;
	}
}
