#include <irc/Server.hpp>
#include <irc/Message.hpp>
#include <utils/atoi.hpp>
#include <utils/strings.hpp>

#include <irc/SocketClient.hpp>
#include <irc/SecureSocketClient.hpp>

#include <utils/Logger.hpp>

#include <ctime>

namespace irc
{
	std::string gHostname = "";

	void
	Server::Registered_Command::
	execute(Server& server, AClient* const user, argumentList const& arguments) const
	{
		if (user->registered)
			payload(server, user, arguments);
		else
			*user << ClientNotResgisteredYet(server.hostname);
	}

	Server::Server()
		:	SocketServer(),
			config(),
			authRequired(false),
			database(this),
			version(SERVER_VERSION)
	{
		gHostname = hostname;
		Logger::instance() << Logger::DEBUG << "Creating empty server..." << std::endl;
	}

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
			database(this),
			version(SERVER_VERSION)
	{
		gHostname = hostname;
	}

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
		maxQueuedActivity = 10; // TODO: Rename to maxQueuedClients and check in man which value to set
		authRequired = !config[IRC_CONF_PASS].empty();
	}

	Server::Command const*	parseCommand(
		std::string::const_iterator& it, std::string::const_iterator& last)
	{
		std::string	name;
		unsigned	i = 0;

		it = parseField(name, it, last);

		if (name.length() == 0)
			return NULL;

		while (i < commandCount
			&& ft::strcmpi(name.c_str(), commands[i]->name.c_str()))
			i++;
		if (i == commandCount)
			return NULL;

		return commands[i];
	}

	Server::connection*	Server::onConnection(int connectionFd,
		Server::connection::address const& address, SSL* sslConnection)
	{
		AClient*	newClient = NULL;

		try {
			if (sslConnection)
				newClient = new SecureSocketClient(sslConnection, connectionFd, address, authRequired);
			else
				newClient = new SocketClient(connectionFd, address, authRequired);
		}
		catch (SocketException const& e)
		{ Logger::instance() << Logger::ERROR << e.what() << ": " << e.why() << std::endl; }

		if (newClient)
		{
			newClient->username = "";
			newClient->nickname = IRC_NICKNAME_DEFAULT;

			Logger::instance() << Logger::INFO << "New connection: "
				<< "\n\tfd: " << connectionFd
				<< "\n\tip: " << address.sin6_addr
				<< "\n\tport: " << address.sin6_port
				<< "\n\tsecure: " << ((sslConnection != NULL) ? "true" : "false")
				<< std::endl;

			// I moved this to the NICK command: database.addClient(newClient);
		}

		return dynamic_cast<Server::connection*>(newClient);
	}

	void	Server::onClientMessage(AClient* const client, Message const& message)
	{
		if (message.command != NULL)
			message.command->execute(*this, client, message.arguments);
	}

	void	Server::onMessage(connection* const connection, std::string const& message)
	{
		AClient*	client = dynamic_cast<AClient*>(connection);
		Message		ircMessage;
		bool		messagesLeft = true;

		client->readBuffer.append(message);

		Logger::instance() << Logger::INFO << client->nickname << ": " << client->readBuffer << std::flush;

		while (messagesLeft)
		{
			try {
				ircMessage = Message(client->readBuffer);
				onClientMessage(client, ircMessage);
			}
			catch(Message::IncompleteMessageException const& e)
			{
				Logger::instance() << Logger::DEBUG << "Waiting for more input..." << std::endl;
				messagesLeft = false;
			}
			catch(Message::MessageException const& e)
			{
				Logger::instance() << Logger::ERROR << e.what() << std::endl;
				client->readBuffer.clear();
				messagesLeft = false;
			}
		}
	}

	void
	Server::
	announceWelcomeSequence(AClient* const user)
	{
		if (!user->registered && user->nickname != IRC_NICKNAME_DEFAULT
		&& !user->username.empty() && user->authenticated)
		{
			//Logger::instance() << Logger::INFO << "Welcome to " << user->nickname << "!" << std::endl;
			*user
			<< WelcomeReply(hostname, user->nickname, user->username, user->hostname)
			<< YourHostReply(hostname, SERVER_VERSION)
			<< CreatedReply(hostname, config[IRC_CONF_CREATEDAT])
			<< MyInfoReply(hostname, SERVER_VERSION, MODES_CLIENT, MODES_CHANNEL);
			user->registered = true;
		}
	}

	std::string
	Server::
	get_local_time()
	throw()
	{
		// Thursday May 20 2021 -- 19:36:00 +00:00

		time_t now = time(NULL);
		tm* const curr_time = localtime(&now);
		return (
			ft::itoa(curr_time->tm_mon + 1) + "/"
			+ ft::itoa(curr_time->tm_mday) + "/"
			+ ft::itoa(curr_time->tm_year + 1900) + " -- "
			+ ft::itoa(curr_time->tm_hour) + ":"
			+ ft::itoa(curr_time->tm_min) + ":"
			+ ft::itoa(curr_time->tm_sec) + " "
			+ curr_time->tm_zone
		);
	}
}
