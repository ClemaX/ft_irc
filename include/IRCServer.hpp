#pragma once

#include <string> // using std::string
#include <list> // using std::list

#include <itoa.hpp>
#include <parseField.hpp>
#include <HashedFileDatabase.hpp>

#include <SocketServer.hpp>
#include <IRCChannel.hpp>
#include <IRCMessage.hpp>
#include <IRCReplies.hpp>

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

		virtual connection*	onConnection(int connectionFd,
			connectionAddress const& address);

		virtual void		onMessage(connection* connection,
			std::string const& message);

	public:

		struct	IRCKickCommand		:	public IRCChannelCommand
		{
			IRCKickCommand();

			virtual bool	execute(IRCServer& server, IRCClient* user,
				argumentList const& arguments) const;
		};

		struct	IRCModeCommand		:	public IRCChannelCommand
		{
			IRCModeCommand();

			virtual bool	execute(IRCServer& server, IRCClient* user,
				argumentList const& arguments) const;
		};

		struct	IRCInviteCommand	:	public IRCChannelCommand
		{
			IRCInviteCommand();

			virtual bool	execute(IRCServer& server, IRCClient* user,
				argumentList const& arguments) const;
		};

		struct	IRCTopicCommand		:	public IRCChannelCommand
		{
			IRCTopicCommand();

			virtual bool	execute(IRCServer& server, IRCClient* user,
				argumentList const& arguments) const;
		};

		struct	IRCPassCommand		:	public IRCCommand
		{
			IRCPassCommand();

			virtual bool	execute(IRCServer& server, IRCClient* user,
				argumentList const& arguments) const;
		};

		struct	IRCJoinCommand		:	public IRCCommand
		{
			IRCJoinCommand();

			virtual bool	execute(IRCServer& server, IRCClient* user,
				argumentList const& arguments) const;
		};

		IRCServer();
		~IRCServer();
	};

	static const IRCServer::IRCJoinCommand	joinCommand;
	static const IRCServer::IRCKickCommand	kickCommand;
	static const IRCServer::IRCModeCommand	modeCommand;
	static const IRCServer::IRCModeCommand	inviteCommand;
	static const IRCServer::IRCTopicCommand	topicCommand;
	static const IRCServer::IRCPassCommand	passCommand;

	static IRCCommand const*const	commands[] =
	{
	  	&joinCommand,
		&kickCommand,
		&modeCommand,
		&inviteCommand,
		&topicCommand,
		&passCommand
	};

	static unsigned const	commandCount = sizeof(commands) / sizeof(*commands);
}

