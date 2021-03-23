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
	class	Server	:	public SocketServer
	{
	private:
		HashedFileDatabase	passwords;

	protected:
		typedef ::std::map<std::string, Channel>	channelMap;

		channelMap	channels;

		virtual connection*	onConnection(int connectionFd,
			connectionAddress const& address);

		virtual void		onMessage(connection* connection,
			std::string const& message);

	public:
		struct	PassCommand		:	public Command
		{
			PassCommand();

			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct	KickCommand		:	public ChannelCommand
		{
			KickCommand();

			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct	ModeCommand		:	public ChannelCommand
		{
			ModeCommand();

			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct	InviteCommand	:	public ChannelCommand
		{
			InviteCommand();

			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct	TopicCommand		:	public ChannelCommand
		{
			TopicCommand();

			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct	JoinCommand		:	public Command
		{
			JoinCommand();

			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		Server();
		~Server();
	};

	static const Server::JoinCommand	joinCommand;
	static const Server::KickCommand	kickCommand;
	static const Server::ModeCommand	modeCommand;
	static const Server::ModeCommand	inviteCommand;
	static const Server::TopicCommand	topicCommand;
	static const Server::PassCommand	passCommand;

	static Command const*const	commands[] =
	{
		&passCommand,
	  	&joinCommand,
		&kickCommand,
		&modeCommand,
		&inviteCommand,
		&topicCommand
	};

	static unsigned const	commandCount = sizeof(commands) / sizeof(*commands);
}

