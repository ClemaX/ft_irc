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
	std::string const& gHostname = "";

	bool
	Server::Registered_Command::
	execute(Server& server, AClient* const user, argumentList const& arguments)
	{
		if (user->registered == true)
			return (payload(server, user, arguments));
		*user << ClientNotResgisteredYet(server.hostname);
		return (false);
	}

	Server::Server()
		:	SocketServer(),
			config(),
			authRequired(false),
			database(this),
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
			database(this),
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
		SocketConnection::address const& address, SSL* sslConnection)
	{
		SocketClient*	newClient = NULL;

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
	}

	void	Server::onMessage(connection* const connection, std::string const& message)
	{
		AClient*	client = dynamic_cast<AClient*>(connection);
		Message		ircMessage;

		client->readBuffer.append(message);

		Logger::instance() << Logger::INFO << client->username << ": " << client->readBuffer << std::flush;

		try { ircMessage = Message(client->readBuffer); }
		catch(Message::IncompleteMessageException const& e)
		{ Logger::instance() << Logger::DEBUG << "Waiting for more input..." << std::endl; }
		catch(Message::MessageException const& e)
		{
			Logger::instance() << Logger::ERROR << e.what() << std::endl;
			client->readBuffer.clear();
		}

		if (ircMessage.command != NULL)
			ircMessage.command->execute(*this, client, ircMessage.arguments);
	}

	void	Server::onFlush() const throw(SocketWriteException)
	{
		// Flush messages
		for (connectionMap::const_iterator it = fdConnectionMap.begin();
			it != fdConnectionMap.end(); ++it)
			dynamic_cast<AClient*>(it->second)->flush();
	}

	void
	Server::
	announceWelcomeSequence(AClient* const user)
	{
		if (!user->registered && user->nickname != IRC_NICKNAME_DEFAULT
		&& !user->username.empty() && user->authenticated)
		{
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
