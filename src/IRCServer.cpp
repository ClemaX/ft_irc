#include <IRCServer.hpp>

namespace irc
{
	IRCServer::IRCServer()	:	SocketServer()
	{ }

	IRCServer::~IRCServer()
	{ }

	IRCServer::connection*	IRCServer::onConnection(int connectionFd,
		connectionAddress const& address)
	{
		IRCChannelClient*	newClient = new IRCChannelClient(address);

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
		IRCChannel	dummyChannel = IRCChannel("dummy");
		IRCChannelClient* client
			= static_cast<IRCChannelClient*>(connection);

		std::cout << client->username << ": " << message;

		IRCMessage const*	ircMessage = new IRCMessage(message);

		if (ircMessage->command)
			ircMessage->command->execute(*client, dummyChannel,
				ircMessage->arguments);
	}
}

