#pragma once

#include <string> // using std::string
#include <list> // using std::list

#include <sstream> // for testing

#include <utils/itoa.hpp>
#include <utils/atoi.hpp>
#include <utils/parseField.hpp>

#include <socket/SocketServer.hpp>
#include <irc/Channel.hpp>
#include <irc/PrivateMessage.hpp>
#include <irc/replies/NumericReply.hpp>
#include <irc/replies/CommandReplies.hpp>
#include <irc/replies/ErrorReplies.hpp>
#include <irc/Client.hpp>
#include <irc/Database.hpp>
#include <irc/ServerConfig.hpp>

// TODO: Grammar rules
// TODO: Handle nicknames containing {}| or []\ (as defined in RFC1459 2.2)
// TODO: Handle message prefix and reject invalid occurences (as defined in RFC1459 2.3)
// TODO: Handle message length including suffix
// TODO: See section 7?

# define CMD_INVITE_NAME "INVITE"
# define CMD_JOIN_NAME "JOIN"
# define CMD_KICK_NAME "KICK"
# define CMD_LIST_NAME "LIST"
# define CMD_NAMES_NAME "NAMES"
# define CMD_PART_NAME "PART"
# define CMD_TOPIC_NAME "TOPIC"
# define CMD_MODE_NAME "MODE"
# define CMD_MOTD_NAME "MOTD"
# define CMD_NICK_NAME "NICK"
# define CMD_NOTICE_NAME "NOTICE"
# define CMD_PASS_NAME "PASS"
# define CMD_PRIVMSG_NAME "PRIVMSG"
# define CMD_USER_NAME "USER"
# define CMD_WHO_NAME "WHO"

namespace NAMESPACE_IRC
{
	template <class __Server, class __Client>
	class Channel;

	extern std::string const&	gHostname;

	class	Server
	: public SocketServer
	{
		/* Server configration */

		const ServerConfig	config;

		protected:

		/* Member types */

		typedef Channel<Server, Client>			__Channel;
		typedef ::std::map<Server*, Server*>	serversMap;
		typedef ::std::map<std::string, __Channel*>	channelsMap;
		typedef IRCDatabase<Server, Client, __Channel> IRCDatabase;

		/* Core members functions */

		virtual connection*	onConnection(int connectionFd,
			connection::address const& address);

		virtual void		onMessage(connection* connection,
			std::string const& message);

		virtual void		onFlush() const throw(SocketWriteException);

		/* Core database */

		public:

		IRCDatabase		database;
		// channelMap	serverChannels;
		// serversMap	neighbourServers;

		/* Member functions */

		Server();
		Server(ServerConfig const& config);
		~Server();

		/* Getters */

		__Channel*			getChannel(const std::string & channelName) const;
		const std::string&	get_hostname() const;

		/* Annouce welcome sequence */

		void		announceWelcomeSequence(Client* user);

		/* Command bases */

		struct Command
		{
			typedef std::vector<std::string>	argumentList;
			std::string const	name;

			Command(std::string const& name);

			virtual bool	payload(Server& server, Client* user,
				argumentList const& arguments) const = 0;
		};

		struct Unregistered_Command
		: public Command
		{
			Unregistered_Command(std::string const& name);

			bool			execute(Server& server, Client* user,
				argumentList const& arguments);
			virtual bool	payload(Server& server, Client* user,
				argumentList const& arguments) const = 0;
		};

		struct Registered_Command
		: public Command
		{
			Registered_Command(std::string const& name);

			bool			execute(Server& server, Client* user,
				argumentList const& arguments);
			virtual bool	payload(Server& server, Client* user,
				argumentList const& arguments) const = 0;
		};

		struct ChannelCommand
		: public Registered_Command
		{
			bool const	isOperatorCommand;

			ChannelCommand(std::string const& name, bool isOperatorCommand);
		};

		/* Group command derivated */

		struct JoinCommand
		: public ChannelCommand
		{
			JoinCommand();

			virtual bool	payload(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct PartCommand
		: public ChannelCommand
		{
			PartCommand();

			virtual bool	payload(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct ModeCommand
		: public ChannelCommand
		{
			ModeCommand();

			virtual bool	payload(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct TopicCommand
		: public ChannelCommand
		{
			TopicCommand();

			virtual bool	payload(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct NamesCommand
		: public ChannelCommand
		{
			NamesCommand();

			virtual bool	payload(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct ListCommand
		: public ChannelCommand
		{
			ListCommand();

			virtual bool	payload(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct InviteCommand
		: public ChannelCommand
		{
			InviteCommand();

			virtual bool	payload(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct KickCommand
		: public ChannelCommand
		{
			KickCommand();

			virtual bool	payload(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		/* Commands non-group derivated */

		struct PassCommand
		: public Unregistered_Command
		{
			PassCommand();

			virtual bool	payload(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct PRIVMSGCommand
		: public Registered_Command
		{
			PRIVMSGCommand();

			virtual bool	payload(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct NoticeCommand
		: public Registered_Command
		{
			NoticeCommand();

			virtual bool	payload(Server& server, Client* user,
				argumentList const& arguments) const;
		};


		struct MotdCommand
		: public Registered_Command
		{
			MotdCommand();

			virtual bool	payload(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct WhoQuery
		: public Registered_Command
		{
			WhoQuery();

			virtual bool	payload(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct NickCommand
		: public Unregistered_Command
		{
			NickCommand();
			virtual bool	payload(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct UserCommand
		: public Unregistered_Command
		{
			UserCommand();
			virtual bool	payload(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		/* Mode parser */

		bool	parseChannelMode(Client *user, std::string const & channelName,
			std::string & flags, std::string & flagArguments);
		bool	parseUserMode(Client *user,	std::string & flags, std::string & flagArguments);

	};

	////////////////////////////
	// Inlined server members //
	////////////////////////////

	inline
	Server::Server()
	: SocketServer(),
	config(), database(this)
	{ hostname = config[IRC_CONF_HOSTNAME]; }

	inline
	Server::Server(ServerConfig const& config)
	: SocketServer(config[IRC_CONF_HOSTNAME], config[IRC_CONF_PORT], 10),
	config(config), database(this)
	{ hostname = config[IRC_CONF_HOSTNAME]; }

	inline
	Server::~Server()
	{ }

	inline Server::__Channel*
	Server::getChannel(const std::string & channelName) const
	{ return (database.getChannel(channelName)); }

	inline const std::string&
	Server::get_hostname() const
	{ return (hostname); }

	///////////////////////////////////
	// Inlined base commands members //
	///////////////////////////////////

	inline
	Server::Command::
	Command(std::string const& name)
	: name(name)
	{ }

	inline
	Server::Unregistered_Command::
	Unregistered_Command(std::string const& name)
	: Command(name)
	{ }

	inline
	Server::Registered_Command::
	Registered_Command(std::string const& name)
	: Command(name)
	{ }

	inline bool
	Server::Unregistered_Command::
	execute(Server& server, Client* user, argumentList const& arguments)
	{ return (payload(server, user, arguments)); }

	inline
	Server::ChannelCommand::
	ChannelCommand(std::string const& name, bool isOperatorCommand)
	: Registered_Command(name), isOperatorCommand(isOperatorCommand)
	{ }

	////////////////////////////////////////////////
	// Inlined derivated channel commands members //
	////////////////////////////////////////////////

	inline
	Server::InviteCommand::
	InviteCommand()
	: ChannelCommand(CMD_INVITE_NAME, true)
	{ }

	inline
	Server::JoinCommand::
	JoinCommand()
	: ChannelCommand(CMD_JOIN_NAME, false)
	{ }

	inline
	Server::KickCommand::
	KickCommand()
	: ChannelCommand(CMD_KICK_NAME, true)
	{ }

	inline
	Server::ListCommand::
	ListCommand()
	: ChannelCommand(CMD_LIST_NAME, true)
	{ }

	inline
	Server::NamesCommand::
	NamesCommand()
	: ChannelCommand(CMD_NAMES_NAME, true)
	{ }

	inline
	Server::PartCommand::
	PartCommand()
	: ChannelCommand(CMD_PART_NAME, true)
	{ }

	inline
	Server::TopicCommand::
	TopicCommand()
	: ChannelCommand(CMD_TOPIC_NAME, true)
	{ }

	////////////////////////////////////////////////
	// Inlined derivated channel commands members //
	////////////////////////////////////////////////

	inline
	Server::ModeCommand::
	ModeCommand()
	: ChannelCommand(CMD_MODE_NAME, true)
	{ }

	inline
	Server::MotdCommand::
	MotdCommand()
	: Registered_Command(CMD_MOTD_NAME)
	{ }

	inline
	Server::NickCommand::
	NickCommand()
	: Unregistered_Command(CMD_NICK_NAME)
	{ }

	inline
	Server::NoticeCommand::
	NoticeCommand()
	: Registered_Command(CMD_NOTICE_NAME)
	{ }

	inline
	Server::PassCommand::
	PassCommand()
	: Unregistered_Command(CMD_PASS_NAME)
	{ }

	inline
	Server::PRIVMSGCommand::
	PRIVMSGCommand()
	: Registered_Command(CMD_PRIVMSG_NAME)
	{ }

	inline
	Server::UserCommand::
	UserCommand()
	: Unregistered_Command(CMD_USER_NAME)
	{ }

	inline
	Server::WhoQuery::
	WhoQuery()
	: Registered_Command(CMD_WHO_NAME)
	{ }

	///////////////////
	// Command utils //
	///////////////////

	Server::Command const*	parseCommand(std::string::const_iterator& it,
		std::string::const_iterator last);

	namespace
	{
		const Server::PassCommand		passCommand;
		const Server::PRIVMSGCommand	privmsgCommand;
		const Server::NoticeCommand		noticeCommand;
		const Server::JoinCommand		joinCommand;
		const Server::PartCommand		partCommand;
		const Server::ModeCommand		modeCommand;
		const Server::TopicCommand		topicCommand;
		const Server::NamesCommand		namesCommand;
		const Server::ListCommand		listCommand;
		const Server::InviteCommand		inviteCommand;
		const Server::KickCommand		kickCommand;
		const Server::MotdCommand		motdCommand;
		const Server::WhoQuery			whoQuery;
		const Server::NickCommand		nickCommand;
		const Server::UserCommand		userCommand;

		Server::Command const*const	commands[] =
		{
			&passCommand,
			&privmsgCommand,
			&noticeCommand,
			&joinCommand,
			&partCommand,
			&modeCommand,
			&topicCommand,
			&namesCommand,
			&listCommand,
			&inviteCommand,
			&kickCommand,
			&motdCommand,
			&whoQuery,
			&nickCommand,
			&userCommand
		};
	}

	void	parseArgumentsQueue(std::string const &argument, std::queue<std::string> &argQueue);
	bool	matchPattern_multiple(std::string const &str, std::string const &pattern);
	bool	matchPattern_unique(std::string const &str, std::string const &pattern);
	bool	matchPattern_global(std::string const &str, std::string const &pattern);

	unsigned const	commandCount = sizeof(commands) / sizeof(*commands);
}
