#include <IRCServer.hpp>

namespace irc
{
	Server::Server()
		:	SocketServer(),
			passwords("passwords.db",
				IRC_NICKNAME_MAXLEN, SHA256_DIGEST_LENGTH * 2)
	{ }

	Server::~Server()
	{ }

	Command const*	parseCommand(
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
		connectionAddress const& address)
	{
		Client*	newClient;

		try { newClient = new Client(connectionFd, address); }
		catch (std::exception const&)
		{
			stop();
			throw;
		}

		newClient->username = "test";

		std::cout << "New connection: "
			<< "fd: " << connectionFd
			<< ", ip: " << address.sin_addr.s_addr
			<< ", port: " << address.sin_port
			<< std::endl;

		return newClient;
	}

	void	Server::onMessage(connection* connection, std::string const& message)
	{
		Client*	client
			= static_cast<Client*>(connection);

		//std::cout << client->username << ": " << connection->buffer;

		Message const*	ircMessage = NULL;

		client->buffer.append(message);

		try { ircMessage = new Message(client->buffer); }
		catch(Message::IncompleteMessageException const& e)
		{ std::cerr << "Waiting for more input..." << std::endl; }
		catch(Message::MessageException const& e)
		{ std::cerr << e.what() << std::endl; } // TODO: Check if we need to delete ircMessage on catch

		if (ircMessage && ircMessage->command)
			ircMessage->command->execute(*this, client, ircMessage->arguments);
	}
}

