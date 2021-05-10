#include <irc/Server.hpp>
#include <irc/Message.hpp>
#include <utils/atoi.hpp>
#include <utils/strings.hpp>

namespace irc
{
	Server::Server()
		:	SocketServer(),
			config()
	{
		database = IRCDatabase(this);	// check to do if the server is directly connected to other servers
	}

	Server::Server(ServerConfig const& config)
		:	SocketServer(config[IRC_CONF_HOSTNAME], config[IRC_CONF_PORT], 10),
			config(config)
	{
		database = IRCDatabase(this);	// check to do if the server is directly connected to other servers
	}

	Server::~Server()
	{ }

	Channel*
	Server::getChannel(const std::string & channelName) const
	{ return database.getChannel(channelName); }

	const std::string&
	Server::get_hostname() const
	{ return (hostname); }

	Server::Command const*	parseCommand(
		std::string::const_iterator& it, std::string::const_iterator last)
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
		connection::address const& address)
	{
		Client*	newClient;

		try { newClient = new Client(connectionFd, address); }
		catch (std::exception const&)
		{
			stop();
			throw;
		}

		newClient->server = this;

		newClient->username = "";
		newClient->nickname = "*";

		std::cout << "New connection: "
			<< "\n\tfd: " << connectionFd
			<< "\n\tip: " << address.sin6_addr
			<< "\n\tport: " << address.sin6_port
			<< std::endl;

		database.addClient(newClient);

		return newClient;
	}

	void	Server::onMessage(connection* connection, std::string const& message)
	{
		Client*	client = static_cast<Client*>(connection);
		Message	ircMessage;

		client->readBuffer.append(message);

		std::cout << client->username << ": " << static_cast<Client*>(connection)->readBuffer;

		try { ircMessage = Message(client->readBuffer); }
		catch(Message::IncompleteMessageException const& e)
		{ std::cerr << "Waiting for more input..." << std::endl; }
		catch(Message::MessageException const& e)
		{
			std::cerr << e.what() << std::endl;
			client->readBuffer.clear();
		}

		if (ircMessage.command)
			ircMessage.command->execute(*this, client, ircMessage.arguments);
	}

	void	Server::onFlush() const throw(SocketWriteException)
	{
		// Flush messages
		for (connectionMap::const_iterator it = fdConnectionMap.begin();
			it != fdConnectionMap.end(); ++it)
			static_cast<Client*>(it->second)->flush();
	}
}
