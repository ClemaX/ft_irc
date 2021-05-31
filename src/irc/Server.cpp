#include <irc/Server.hpp>
#include <irc/Message.hpp>
#include <utils/atoi.hpp>
#include <utils/strings.hpp>

#include <irc/SocketClient.hpp>
#include <irc/SecureSocketClient.hpp>

#include <irc/ServerConnection.hpp>

#include <utils/Logger.hpp>

#include <ctime>


namespace irc
{
	namespace
	{
		const PRIVMSGCommand	privmsgCommand;
		const NoticeCommand		noticeCommand;
		const MotdCommand		motdCommand;
		const WhoQuery			whoCommand;
		const NickCommand		nickCommand;
		const UserCommand		userCommand;
		const OperCommand		operCommand;
		const VersionCommand	versionCommand;
		const JoinCommand		joinCommand;
		const PartCommand		partCommand;
		const ModeCommand		modeCommand;
		const TopicCommand		topicCommand;
		const NamesCommand		namesCommand;
		const ListCommand		listCommand;
		const InviteCommand		inviteCommand;
		const KickCommand		kickCommand;
		const TimeCommand		timeCommand;
		const StatsCommand		statsCommand;
		const AdminCommand		adminCommand;
		const RestartCommand	restartCommand;
		const RehashCommand		rehashCommand;
	}

	// cat include/irc/commands/ClientCommands.hpp | grep -v "^\s//" | grep struct | cut -d " " -f2 | grep -v "struct" | sed -e "s/$/(),/g" -e "s/^/\&/g"
	irc::ClientCommand const*const	Server::clientCommands[] =
	{
		&privmsgCommand,
		&noticeCommand,
		&motdCommand,
		&whoCommand,
		&nickCommand,
		&userCommand,
		&operCommand,
		&versionCommand,
		&joinCommand,
		&partCommand,
		&modeCommand,
		&topicCommand,
		&namesCommand,
		&listCommand,
		&inviteCommand,
		&kickCommand,
		&timeCommand,
		&statsCommand,
		&adminCommand,
		&restartCommand,
		&rehashCommand,
	};

	std::string const& gHostname = "";

	Server::Server()
		:	SocketServer(),
			config(),
			authRequired(false),
			database(config),
			version(SERVER_VERSION)
	{ Logger::instance() << Logger::DEBUG << "Creating empty server..." << std::endl; } // TODO: Maybe init hostname

	Server::Server(ServerConfig const& config)
		throw(SSLContextException, SocketException)
		:	SocketServer(
				config[IRC_CONF_HOSTNAME],
				config[IRC_CONF_PORT],
				config[IRC_CONF_SSLPORT],
				config[IRC_CONF_SSLCERT],
				config[IRC_CONF_SSLKEY],
				10
			),
			config(config),
			authRequired(!config[IRC_CONF_PASS].empty()),
			database(config),
			version(SERVER_VERSION)
	{ }

	Server::~Server()
	{ }

	/* void	Server::loadConfig(ServerConfig const& config)
	{
		hostname = config[IRC_CONF_HOSTNAME];
		port = config[IRC_CONF_PORT];
		sslPort = config[IRC_CONF_SSLPORT];
		sslContext = ssl::Context()
	} */

	void Server::loadConfig(ServerConfig const& newConfig)
		throw(SSLContextException, SocketException)
	{
		config = newConfig;
		hostname = config[IRC_CONF_HOSTNAME];
		port = config[IRC_CONF_PORT];
		sslPort = config[IRC_CONF_SSLPORT];
		if (!sslPort.empty())
			context.loadCertificate(config[IRC_CONF_SSLCERT], config[IRC_CONF_SSLKEY]);
		maxClients = 10; // TODO: Rename to maxQueuedClients and check in man which value to set
		authRequired = !config[IRC_CONF_PASS].empty();
	}

/*
	Server::connection*	Server::onConnection(int connectionFd,
		SocketConnection::address const& address, SSL* sslConnection)
	{
		ABufferedConnection*	newClient = NULL;

		try {
			if (sslConnection)
				newClient = new SecureSocketClient(sslConnection, connectionFd, address, authRequired);
			else
				newClient = new SocketClient(connectionFd, address, authRequired);
		}
		catch (...)
		{ stop(); throw; }

		//newClient->server = this;

		newClient->username = "";
		newClient->nickname = IRC_NICKNAME_DEFAULT;

		Logger::instance() << Logger::INFO << "New connection: "
			<< "\n\tfd: " << connectionFd
			<< "\n\tip: " << address.sin6_addr
			<< "\n\tport: " << address.sin6_port
			<< "\n\tsecure: " << ((sslConnection != NULL) ? "true" : "false")
			<< std::endl;

		// I moved this to the NICK command: database.addClient(newClient);

		return newClient;
	} */

	void	Server::onClientMessage(AClient *client, Message<ClientCommand> const& message)
	{
		message.command->payload(database, client, message.arguments);
	}

	void	Server::onServerMessage(AServerConnection *server, Message<ServerCommand> const& message)
	{
		message.command->payload(database, server, message.arguments);
	}
	void	Server::onMessage(connection* const connection, std::string const& message)
	{
		// TODO: Use template on SocketServer to avoid casts in implementation
		ABufferedConnection *bufferedConnection = dynamic_cast<ABufferedConnection*>(connection);

		if (bufferedConnection)
		{
			Message<ABufferedConnection>	ircMessage;

			bufferedConnection->readBuffer += message;

			Logger::instance() << Logger::INFO << bufferedConnection->getUid() << ": " << bufferedConnection->readBuffer << std::flush;
		}
/* 		if (client)
		{


			try { ircMessage = Message(client->readBuffer); }
			catch(Message::IncompleteMessageException const& e)
			{ Logger::instance() << Logger::DEBUG << "Waiting for more input..." << std::endl; }
			catch(Message::MessageException const& e)
			{
				Logger::instance() << Logger::ERROR << e.what() << std::endl;
				client->readBuffer.clear();
			}

			if (ircMessage.command != NULL)
				onClientMessage(client, ircMessage);
		}
		else
		{
			AServerConnection*	server = dynamic_cast<AServerConnection*>(connection);

			server->readBuffer += ircMessage;

			Logger::instance() << Logger::INFO << server->name << ": " << server->readBuffer << std::flush;

			try { ircMessage = Message(server->readBuffer); }
			catch(Message::MessageException const& e)
			{
				Logger::instance() << Logger::ERROR << e.what() << std::endl;
				server->readBuffer.clear();
			}

			if (ircMessage.command != NULL)
				onServerMessage(client, ircMessage);
		} */
	}

	void	Server::onFlush() const throw(SocketWriteException)
	{
		// Flush messages
		for (connectionMap::const_iterator it = fdConnectionMap.begin();
			it != fdConnectionMap.end(); ++it)
			dynamic_cast<AClient*>(it->second)->flush();
	}
}
