#include <IRCServer.hpp>

namespace irc
{
	SocketConnection const&	operator<<(SocketConnection const& client, IReply const& message)
	{
		client << message.serialize();

		return client;
	}


// --- command KICK ---//
	Server::KickCommand::KickCommand()
		:	ChannelCommand("KICK", true)
	{ }

	bool	Server::KickCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		(void)server;
		(void)arguments;
		std::cout << user->username << " executes " << name << std::endl;
		return false;
	}

// --- command MODE ---//
	Server::ModeCommand::ModeCommand()
		:	ChannelCommand("MODE", true)
	{ }

	bool	Server::ModeCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		(void)server;
		(void)arguments;
		std::cout << user->username << " executes " << name << std::endl;
		return false;
	}

// --- command INVITE ---//
	Server::InviteCommand::InviteCommand()
		:	ChannelCommand("INVITE", true)
	{ }

	bool	Server::InviteCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		(void)server;
		(void)arguments;
		std::cout << user->username << " executes " << name << std::endl;
		return false;
	}

// --- command TOPIC ---//
	Server::TopicCommand::TopicCommand()
		:	ChannelCommand("TOPIC", true)
	{ }

	bool	Server::TopicCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		if (!arguments.size())
			return false; // throw exeception ?

		const std::string channelName = arguments[0];
		Channel	*channel = server.getChannel(channelName);

		if (!channel)
			; // throw exception ?
		else if (!channel->isOperator(user))
			; // throw exception ?
		else if (arguments.size() == 1)
			std::cout << channel->getTopic() << "\n";
		else
		{
			const std::string newTopic = arguments[1];
			channel->setTopic(newTopic);
		}
		return true;
	}

// --- command PASS ---//
	Server::PassCommand::PassCommand()
		:	Command("PASS")
	{ }

	bool	Server::PassCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		(void)server;
		std::cout << user->username << " executes " << name << std::endl;

		if (!arguments.size())
		{
			*user << NeedMoreParamsReply("localhost", name); // << user->nickname << ft::itoa(_ERR_NEEDMOREPARAMS);
			return false;
		}
		std::cout << "Setting password '" << arguments[0] << "'" << std::endl;
		return true;
	}

// --- command JOIN ---//
	Server::JoinCommand::JoinCommand()
		:	ChannelCommand("JOIN", false)
	{ }

	bool	Server::JoinCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		bool isOp = false;
		const std::string channelName = arguments[0];
		Channel *channel;

		if (server.database->dataChannelsMap.find(channelName) == server.database->dataChannelsMap.end())	// search channel in serverChannels map
		{
			channel = new Channel(channelName);
			server.database->dataChannelsMap[channelName] = channel;	// Create the channel if it doesn't exist
			isOp = true;										// will set user as operator
			channel->addServer(&server);		// add server to the channel servers list
		}
		else
			channel = (server.database->dataChannelsMap.find(channelName))->second;
		user->joinChannel(channel);
		return channel->addClient(user, isOp);

	}

// --- command PART ---//
	Server::PartCommand::PartCommand()
		:	ChannelCommand("PART", true)
	{ }

	bool	Server::PartCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		(void)server;
		const std::string channelName = arguments[0];

		if (user->clientChannels.find(channelName) == user->clientChannels.end())
			return false;
		user->leaveChannel(user->clientChannels[channelName]);
		return true;
	}

	Server::MotdCommand::MotdCommand()
		:	Command("MOTD")
	{ }

	bool	Server::MotdCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		std::cout << user->username << " executes " << name << std::endl;

		*user << serializeReplyList<MotdStartReply, MotdReply, EndOfMotdReply>("localhost", user->nickname, server.motd, '\n', 80);

		if (arguments.size())
		{
			// TODO: Route to server
			std::cout << "Arguments: ";
			for (argumentList::const_iterator it = arguments.begin();
				it != arguments.end(); it++)
				std::cout << *it << ", ";
			std::cout << std::endl;
		}
		return false;
	}
}
