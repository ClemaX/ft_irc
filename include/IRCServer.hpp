#pragma once

#include <string> // using std::string
#include <list> // using std::list

#include <parseField.hpp>
#include <HashedFileDatabase.hpp>

#include <SocketServer.hpp>
#include <IRCChannel.hpp>
#include <IRCMessage.hpp>

// TODO: Grammar rules
// TODO: Handle nicknames containing {}| or []\ (as defined in RFC1459 2.2)
// TODO: Handle message prefix and reject invalid occurences (as defined in RFC1459 2.3)
// TODO: Handle message length including suffix
// TODO: See section 7?


namespace irc
{
	class	IRCServer	:	public SocketServer
	{
	private:
		HashedFileDatabase	passwords;

	protected:
		typedef ::std::map<std::string, IRCChannel>	channelMap;

		channelMap	channels;

		virtual connection* onConnection(int connectionFd,
			connectionAddress const& address);

		virtual void	onMessage(connection* connection,
			std::string const& message);

	public:

		struct	IRCKickCommand		:	public IRCChannelCommand
		{
			IRCKickCommand()	:	IRCChannelCommand("KICK", true)
			{ }
			virtual bool	execute(IRCServer& server, IRCClient const* user,
				argumentList const& arguments) const
			{
				(void)server;
				(void)arguments;
				std::cout << user->username << " executes " << name << std::endl;
				return false;
			}
		};

		struct	IRCModeCommand		:	public IRCChannelCommand
		{
			IRCModeCommand()	:	IRCChannelCommand("MODE", true)
			{ }
			virtual bool	execute(IRCServer& server, IRCClient const* user,
				argumentList const& arguments) const
			{
				(void)server;
				(void)arguments;
				std::cout << user->username << " executes " << name << std::endl;
				return false;
			}
		};

		struct	IRCInviteCommand	:	public IRCChannelCommand
		{
			IRCInviteCommand()	:	IRCChannelCommand("INVITE", true)
			{ }
			virtual bool	execute(IRCServer& server, IRCClient const* user,
				argumentList const& arguments) const
			{
				(void)server;
				(void)arguments;
				std::cout << user->username << " executes " << name << std::endl;
				return false;
			}
		};

		struct	IRCTopicCommand		:	public IRCChannelCommand
		{
			IRCTopicCommand()	:	IRCChannelCommand("TOPIC", true)
			{ }
			virtual bool	execute(IRCServer& server, IRCClient const* user,
				argumentList const& arguments) const
			{
				(void)server;
				(void)arguments;
				std::cout << user->username << " executes " << name << std::endl;
				return false;
			}
		};

		struct	IRCJoinCommand		:	public IRCCommand
		{
			IRCJoinCommand()	:	IRCCommand("JOIN")
			{ }
			virtual bool	execute(IRCServer& server, IRCClient const* user,
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
		};

		IRCServer();
		~IRCServer();
	};

	static const IRCServer::IRCJoinCommand	joinCommand;
	static const IRCServer::IRCKickCommand	kickCommand;
	static const IRCServer::IRCModeCommand	modeCommand;
	static const IRCServer::IRCModeCommand	inviteCommand;
	static const IRCServer::IRCTopicCommand	topicCommand;


	static IRCCommand const*const	commands[] =
	{
	  	&joinCommand,
		&kickCommand,
		&modeCommand,
		&inviteCommand,
		&topicCommand
	};

	static unsigned const	commandCount = sizeof(commands) / sizeof(*commands);

	IRCCommand const*	parseCommand(std::string::const_iterator& it,
		std::string::const_iterator last);
}

