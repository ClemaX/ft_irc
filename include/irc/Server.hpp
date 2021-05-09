#pragma once

#include <string> // using std::string
#include <list> // using std::list

#include <sstream> // for testing

#include <utils/itoa.hpp>
#include <utils/atoi.hpp>
#include <utils/parseField.hpp>
#include <HashedFileDatabase.hpp>

#include <socket/SocketServer.hpp>
#include <irc/Channel.hpp>
#include <irc/PrivateMessage.hpp>
#include <irc/replies/NumericReplies.hpp>
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


namespace irc
{
	class Channel;

	class	Server	:	public SocketServer
	{
	private:
		const ServerConfig	config;
		HashedFileDatabase	passwords;

	protected:
		typedef ::std::map<Server*, Server*>	serversMap;
		typedef ::std::map<std::string, Channel*>	channelsMap;
		// typedef ::std::pair<std::string, Channel*>	channelPair;

		virtual connection*	onConnection(int connectionFd,
			connection::address const& address);

		virtual void		onMessage(connection* connection,
			std::string const& message);

		virtual void		onFlush() const throw(SocketWriteException);

	public:
		IRCDatabase			database;
		// channelMap	serverChannels;
		// serversMap	neighbourServers;

		Server();
		Server(ServerConfig const& config);

		~Server();

		Channel *getChannel(const std::string & channelName) const;
		const std::string& get_hostname() const;

		struct	Command
		{
			typedef std::vector<std::string>	argumentList;
			std::string const	name;

			Command(std::string const& name);

			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const = 0;
		};

		struct	PassCommand		:	public Command
		{
			PassCommand();

			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct	PRIVMSGCommand		:	public Command
		{
			PRIVMSGCommand();

			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const;
		};

// ============================================== //
// ============================================== //
		struct	ChannelCommand	:	public Command
		{
			bool const	isOperatorCommand;

			ChannelCommand(std::string const& name, bool isOperatorCommand);
		};
// ============================================== //
		struct	JoinCommand		:	public ChannelCommand
		{
			JoinCommand();

			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct	PartCommand		:	public ChannelCommand
		{
			PartCommand();

			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct	ModeCommand		:	public ChannelCommand
		{
			ModeCommand();

			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct	TopicCommand	:	public ChannelCommand
		{
			TopicCommand();

			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct	NamesCommand		:	public ChannelCommand
		{
			NamesCommand();

			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct	ListCommand		:	public ChannelCommand
		{
			ListCommand();

			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct	InviteCommand	:	public ChannelCommand
		{
			InviteCommand();

			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct	KickCommand		:	public ChannelCommand
		{
			KickCommand();

			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const;
		};
// ============================================== //
// ============================================== //
		struct	MotdCommand		:	public Command
		{
			MotdCommand();

			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct	WhoQuery		:	public Command
		{
			WhoQuery();

			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct NickCommand
		: public Command
		{
			NickCommand();
			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		struct UserCommand
		: public Command
		{
			UserCommand();
			virtual bool	execute(Server& server, Client* user,
				argumentList const& arguments) const;
		};

		bool	parseChannelMode(Client *user, std::string const & channelName,
			std::string & flags, std::string & flagArguments);
		bool	parseUserMode(Client *user,	std::string & flags, std::string & flagArguments);

	};

	Server::Command const*	parseCommand(std::string::const_iterator& it,
		std::string::const_iterator last);

	namespace
	{
		const Server::PassCommand		passCommand;
		const Server::PRIVMSGCommand	privmsgCommand;
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

	static unsigned const	commandCount = sizeof(commands) / sizeof(*commands);
}
