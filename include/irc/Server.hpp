#pragma once

#include <string> // using std::string
#include <list> // using std::list

#include <sstream> // for testing

#include <utils/itoa.hpp>
#include <utils/atoi.hpp>
#include <utils/parseField.hpp>

#include <socket/SocketServer.hpp>

#include <irc/Database.hpp>

#include <irc/Channel.hpp>

#include <irc/Message.hpp>
#include <irc/PrivateMessage.hpp>

#include <irc/replies/NumericReply.hpp>
#include <irc/replies/CommandReplies.hpp>
#include <irc/replies/ErrorReplies.hpp>

#include <irc/AClient.hpp>
#include <irc/ServerConfig.hpp>

#include <irc/AServerConnection.hpp>

#include <irc/commands/ClientCommands.hpp>
#include <irc/commands/ServerCommands.hpp>
#include <irc/commands/UnauthenticatedCommand.hpp>

// TODO: Grammar rules
// TODO: Handle nicknames containing {}| or []\ (as defined in RFC1459 2.2)
// TODO: Handle message prefix and reject invalid occurences (as defined in RFC1459 2.3)
// TODO: Handle message length including suffix
// TODO: See section 7?

/* Do not need this (only makes things more complex)
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
# define CMD_ADMIN_NAME "ADMIN" */

namespace NAMESPACE_IRC
{
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
		// TODO: Map servers by name
		//typedef ::std::map<std::string, Server*>	serversMap;

	protected:
		static ClientCommand const*const			clientCommands[];
		static ServerCommand const*const			serverCommands[];
		static UnauthenticatedCommand const*const	unauthenticatedCommands[];
		/* Core members functions */

/*		connection*	onConnection(int connectionFd,
			SocketConnection::address const& address, SSL* sslConnection = NULL); */

		void		onClientMessage(AClient* const client,
			Message<ClientCommand> const& message);

		// TODO: Send ERROR command in case of invalid SERVER message
		void		onServerMessage(AServerConnection* const server,
			Message<ServerCommand> const& message);

		void		onMessage(connection* const connection,
			std::string const& message);

		void		onFlush() const throw(SocketWriteException);

		/* Core database */

		public:

		Database			database;
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

		/* Get local time */
		// TODO: This should obviously be in utils...
		//std::string	getLocalTime() throw();

		/* Command bases */
/*
		struct UnauthenticatedCommand
		: public Command
		{
			UnauthenticatedCommand(std::string const& name);

			bool			execute(Server& server, AClient* const user,
				argumentList const& arguments);
			virtual bool	payload(Server& server, AClient* const user,
				argumentList const& arguments) const = 0;
		};
 */
		/* Group command derivated */


		/* Commands non-group derivated */


		/* Server commands */

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

	////////////////////////////////////////////////
	// Inlined derivated channel commands members //
	////////////////////////////////////////////////0

	////////////////////////////////////////////////
	// Inlined derivated channel commands members //
	////////////////////////////////////////////////

	///////////////////////////////////////////////
	// Inlined derivated serevr commands members //
	///////////////////////////////////////////////

	///////////////////
	// Command utils //
	///////////////////
}
