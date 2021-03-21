#include <IRCServer.hpp>

namespace irc
{
	IRCServer::IRCServer()
		:	SocketServer(),
			passwords("passwords.db",
				IRC_NICKNAME_MAXLEN, SHA256_DIGEST_LENGTH * 2)
	{ }

	IRCServer::~IRCServer()
	{ }

	IRCCommand const*	parseCommand(
		std::string::const_iterator& it, std::string::const_iterator last)
	{
		std::string	name;
		unsigned	i = 0;

		it = parseField(name, it, last);

		std::cout << "Command candidate " << name << std::endl;
		if (name.length() == 0)
			return NULL;

		while (i < commandCount && name != commands[i]->name)
			i++;
		if (i == commandCount)
			return NULL;

		return commands[i];
	}

	IRCServer::connection*	IRCServer::onConnection(int connectionFd,
		connectionAddress const& address)
	{
		IRCClient*	newClient;

		try { newClient = new IRCClient(connectionFd, address); }
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

	void	IRCServer::onMessage(connection* connection,
		std::string const& message)
	{
		IRCClient*	client
			= static_cast<IRCClient*>(connection);

		std::cout << client->username << ": " << message;

		IRCMessage const*	ircMessage = NULL;
		try
		{ ircMessage = new IRCMessage(message); }
		catch(IRCMessage::IRCMessageException const& e)
		{ std::cerr << e.what() << ": " << message << std::endl; }

		if (ircMessage && ircMessage->command)
			ircMessage->command->execute(*this, client, ircMessage->arguments);
	}
}

