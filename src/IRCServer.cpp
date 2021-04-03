#include <IRCServer.hpp>
#include <IRCMessage.hpp>

namespace irc
{
	Server::Server()
		:	SocketServer(),
			passwords("passwords.db", IRC_NICKNAME_MAXLEN,
				SHA256_DIGEST_LENGTH * 2),
			motd("Hello client!\nWelcome on ircserv!")
	{
		database = new IRCDatabase(this);	// check to do if the server is directly connected to other servers
	}

	Server::~Server()
	{ }

	Channel *Server::getChannel(const std::string & name) const
	{
		channelsMap::iterator it = database->dataChannelsMap.find(name);

		if (it == database->dataChannelsMap.end())	// search channel in serverChannels map
			return NULL;
		return it->second;
	}

	Server::Command const*	parseCommand(
		std::string::const_iterator& it, std::string::const_iterator last)
	{
		std::string	name;
		unsigned	i = 0;

		it = parseField(name, it, last);

		if (name.length() == 0)
			return NULL;

		while (i < commandCount && name != commands[i]->name)
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

		newClient->username = "testName";
		newClient->nickname = "testNick";

	/////////////////////////////////////////////	for testing
		std::stringstream ss;  
  		ss << newClient->username << rand() % 10;
		newClient->username = ss.str();
	/////////////////////////////////////////////

		std::cout << "New connection: "
			<< "\n\tfd: " << connectionFd
			<< "\n\tip: " << address.sin_addr.s_addr
			<< "\n\tport: " << address.sin_port
			<< std::endl;

		return newClient;
	}

	void	Server::onMessage(connection* connection, std::string const& message)
	{
		Client*	client
			= static_cast<Client*>(connection);


		Message const*	ircMessage = NULL;

		client->readBuffer.append(message);

		std::cout << client->username << ": " << static_cast<Client*>(connection)->readBuffer;

		try { ircMessage = new Message(client->readBuffer); }
		catch(Message::IncompleteMessageException const& e)
		{ std::cerr << "Waiting for more input..." << std::endl; }
		catch(Message::MessageException const& e)
		{
			std::cerr << e.what() << std::endl;
			client->readBuffer.clear();
		} // TODO: Check if we need to delete ircMessage on catch

		if (ircMessage && ircMessage->command)
			ircMessage->command->execute(*this, client, ircMessage->arguments);
	}

	void	Server::onFlush() const throw(SocketWriteException)
	{
		// Flush messages
		for (connectionMap::const_iterator it = fdConnectionMap.begin();
			it != fdConnectionMap.end(); ++it)
			static_cast<Client*>(it->second)->flush();
	}
}
