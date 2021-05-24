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
#include <irc/AClient.hpp>
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
# define CMD_VERSION_NAME "VERSION"
# define CMD_USERS_NAME "USERS"
# define CMD_TIME_NAME "TIME"
# define CMD_STATS_NAME "STATS"
# define CMD_SQUIT_NAME "SQUIT"
# define CMD_SERVER_NAME "SERVER"
# define CMD_RESTART_NAME "RESTART"
# define CMD_REHASH_NAME "REHASH"
# define CMD_OPER_NAME "OPER"
# define CMD_ADMIN_NAME "ADMIN"

namespace NAMESPACE_IRC
{
	template <class __Server, class __AClient>
	class Channel;

	extern std::string const&	gHostname;

	struct ServerAdmin
	{
		typedef std::pair<std::string, std::string> pair_t;

		// TO DO: Should be init in the config file

		const pair_t		id;
		const std::string	data1;
		const std::string	data2;
		const std::string	email;

		ServerAdmin(const pair_t& __id = pair_t(IRC_DFT_ADMIN_NICK, IRC_DFT_ADMIN_PASS),
			const std::string& __data1 = IRC_DFT_ADMIN_PASS,
			const std::string& __data2 = IRC_DFT_ADMIN_DATA1,
			const std::string& __email = IRC_DFT_ADMIN_DATA2)
		: id(__id), data1(__data1), data2(__data2), email(__email)
		{ }
	};

	class	Server
	: public SocketServer
	{
	private:
		/* Server configration */
		ServerConfig	config;
		bool			authRequired;

		/* Member types */

		typedef Channel<Server, AClient>			__Channel;
		// TODO: Map servers by name
		typedef ::std::map<std::string, Server*>	serversMap;
		typedef ::std::map<std::string, __Channel*>	channelsMap;
		typedef IRCDatabase<Server, AClient, __Channel> IRCDatabase;


		protected:

		/* Core members functions */

		connection*	onConnection(int connectionFd,
			SocketConnection::address const& address, SSL* sslConnection = NULL);

		void		onMessage(connection* const connection,
			std::string const& message);

		void		onFlush() const throw(SocketWriteException);

		/* Core database */

		public:

		IRCDatabase			database;
		ServerAdmin			admin;
		const std::string	version;
		// channelMap	serverChannels;
		// serversMap	neighbourServers;

		/* Member functions */

		Server();
		Server(ServerConfig const& config)
			throw(SSLContextException, SocketException);

		~Server();

		void	loadConfig(ServerConfig const& config)
			throw(SSLContextException, SocketException);

		/* Getters */
		//__Channel*			getChannel(const std::string & channelName) const;
		const std::string&	get_hostname() const;

		// Are these comments really helpful??
		/* Annouce welcome sequence */

		void		announceWelcomeSequence(AClient* const user);

		/* Get local time */

		std::string	get_local_time() throw();

		/* Command bases */

		class Command
		{
			Command();
			Command(const Command&);
			Command& operator=(const Command&);

			public:

			typedef std::vector<std::string>	argumentList;

			std::string const	name;

			Command(const std::string& __name);

			virtual ~Command();

			virtual bool	execute(Server& server, AClient* const user,
				argumentList const& arguments) = 0;
			virtual bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const = 0;
		};

		struct Unregistered_Command
		: public Command
		{
			Unregistered_Command(std::string const& name);

			bool			execute(Server& server, AClient* const user,
				argumentList const& arguments);
			virtual bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const = 0;
		};

		struct Registered_Command
		: public Command
		{
			Registered_Command(std::string const& name);

			bool			execute(Server& server, AClient* const user,
				argumentList const& arguments);
			virtual bool	payload(Server& server, AClient* const user,
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

			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		struct PartCommand
		: public ChannelCommand
		{
			PartCommand();

			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		struct ModeCommand
		: public ChannelCommand
		{
			ModeCommand();

			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		struct TopicCommand
		: public ChannelCommand
		{
			TopicCommand();

			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		struct NamesCommand
		: public ChannelCommand
		{
			NamesCommand();

			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		struct ListCommand
		: public ChannelCommand
		{
			ListCommand();

			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		struct InviteCommand
		: public ChannelCommand
		{
			InviteCommand();

			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		struct KickCommand
		: public ChannelCommand
		{
			KickCommand();

			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		/* Commands non-group derivated */

		struct PassCommand
		: public Unregistered_Command
		{
			PassCommand();

			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		struct PRIVMSGCommand
		: public Registered_Command
		{
			PRIVMSGCommand();

			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		struct NoticeCommand
		: public Registered_Command
		{
			NoticeCommand();

			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};


		struct MotdCommand
		: public Registered_Command
		{
			MotdCommand();

			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		struct WhoQuery
		: public Registered_Command
		{
			WhoQuery();

			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		struct NickCommand
		: public Unregistered_Command
		{
			NickCommand();
			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		struct UserCommand
		: public Unregistered_Command
		{
			UserCommand();
			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		struct OperCommand
		: public Registered_Command
		{
			OperCommand();

			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		/* Server commands */

		// TO DO: All Registered_Commads by default but need to test to be sure (but is the most logical)

		struct VersionCommand
		: Registered_Command
		{
			VersionCommand();
			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		struct UsersCommand
		: Registered_Command
		{
			UsersCommand();
			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};


		struct TimeCommand
		: Registered_Command
		{
			TimeCommand();
			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		struct StatsCommand
		: Registered_Command
		{
			StatsCommand();
			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		struct SquitCommand
		: Registered_Command
		{
			SquitCommand();
			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		struct ServerCommand
		: Registered_Command
		{
			ServerCommand();
			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		struct RestartCommand
		: Registered_Command
		{
			RestartCommand();
			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		struct RehashCommand
		: Registered_Command
		{
			RehashCommand();
			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		struct AdminCommand
		: Registered_Command
		{
			AdminCommand();
			bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const;
		};

		/* Mode parser */

		bool	parseChannelMode(AClient* const user, std::string const & channelName,
			std::string & flags, std::string & flagArguments);
		bool	parseUserMode(AClient *const user,	std::string & flags, std::string & flagArguments);

	};

	////////////////////////////
	// Inlined server members //
	////////////////////////////
	// TODO: Debate about using inline constructors

/*
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

	Server::~Server()
	{ }
*/
/*
	inline Server::__Channel*
	Server::getChannel(const std::string & channelName) const
	{ return (database.getChannel(channelName)); } */

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
	Server::Command::
	~Command()
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
	execute(Server& server, AClient* const user, argumentList const& arguments)
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

	inline
	Server::OperCommand::
	OperCommand()
	: Registered_Command(CMD_OPER_NAME)
	{ }

	///////////////////////////////////////////////
	// Inlined derivated serevr commands members //
	///////////////////////////////////////////////

	inline
	Server::VersionCommand::
	VersionCommand()
	: Registered_Command(CMD_VERSION_NAME)
	{ }

	inline
	Server::UsersCommand::
	UsersCommand()
	: Registered_Command(CMD_USERS_NAME)
	{ }

	inline
	Server::TimeCommand::
	TimeCommand()
	: Registered_Command(CMD_TIME_NAME)
	{ }

	inline
	Server::StatsCommand::
	StatsCommand()
	: Registered_Command(CMD_STATS_NAME)
	{ }

	inline
	Server::SquitCommand::
	SquitCommand()
	: Registered_Command(CMD_SQUIT_NAME)
	{ }

	inline
	Server::ServerCommand::
	ServerCommand()
	: Registered_Command(CMD_SERVER_NAME)
	{ }

	inline
	Server::RestartCommand::
	RestartCommand()
	: Registered_Command(CMD_RESTART_NAME)
	{ }

	inline
	Server::RehashCommand::
	RehashCommand()
	: Registered_Command(CMD_REHASH_NAME)
	{ }

	inline
	Server::AdminCommand::
	AdminCommand()
	: Registered_Command(CMD_ADMIN_NAME)
	{ }

	///////////////////
	// Command utils //
	///////////////////

	Server::Command const*	parseCommand(std::string::const_iterator& it,
		std::string::const_iterator& last);

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
		const Server::VersionCommand	versionCommand;
		const Server::UsersCommand		usersCommand;
		const Server::TimeCommand		timeCommand;
		const Server::StatsCommand		statsCommand;
		const Server::SquitCommand		squitCommand;
		const Server::ServerCommand		serverCommand;
		const Server::RestartCommand	restartCommand;
		const Server::RestartCommand	rehashCommand;
		const Server::OperCommand		operCommand;
		const Server::AdminCommand		adminCommand;

		Server::Command const*const	commands[] =
		{
			&passCommand,	 &privmsgCommand, &noticeCommand,
			&joinCommand,	 &partCommand,	  &modeCommand,
			&topicCommand,	 &namesCommand,	  &listCommand,
			&inviteCommand,	 &kickCommand,	  &motdCommand,
			&whoQuery,		 &nickCommand,	  &userCommand,
			&versionCommand, &usersCommand,	  &timeCommand,
			&statsCommand,	 &squitCommand,	  &serverCommand,
			&restartCommand, &restartCommand, &operCommand,
			&adminCommand
		};
	}

	void	parseArgumentsQueue(std::string const &argument, std::queue<std::string> &argQueue);
	bool	matchPattern_multiple(std::string const &str, std::string const &pattern);
	bool	matchPattern_unique(std::string const &str, std::string const &pattern);
	bool	matchPattern_global(std::string const &str, std::string const &pattern);

	unsigned const	commandCount = ARRAY_SIZE(commands);
}
