#include <IRCServer.hpp>

namespace irc
{
	SocketConnection const&	operator<<(SocketConnection const& client, IReply const& message)
	{
		client << message.serialize();

		return client;
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


// ============   CHANNEL commands   ============ //

// --- command KICK ---//
	Server::KickCommand::KickCommand()
		:	ChannelCommand("KICK", true)
	{ }

	bool	Server::KickCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		(void)server;
		if (arguments.size() < 2)
			return false;
		std::string channelName = arguments[0];
		std::string clientNickname = arguments[1]; // do we check the username ? Nickname ?

		if (!user->isInChannel(channelName))
			return false;
		Channel *channel = user->getChannel(channelName);
		if (!channel->isOperator(user))
			return false;		
		Client *victim = channel->getUser(clientNickname); // do we check the username ? Nickname ?
		if (!victim)	// if victim not found in channel
			return false;
		
		victim->leaveChannel(channelName);

		if (arguments.size() > 2 && arguments[2][0] == IRC_MESSAGE_PREFIX_PREFIX)
		{
			std::string comment = arguments[2];
			comment.erase(0,1);
			std::cout << "Reason: \"" << comment << "\"\n";
		}
		return true;
	}

//////////////////////////////////////////////////////////////////////////////////

// --- command MODE ---//
	Server::ModeCommand::ModeCommand()
		:	ChannelCommand("MODE", true)
	{ }

	bool	Server::ModeCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		(void)server;
		if (arguments.size() < 2)
			return false;
		
		std::string nameArgument = arguments[0];
		std::string flags = arguments[1];
		if (!flags.size())
			return false;	// necessary ?

		std::string	flagArgument = "";
		if (arguments.size() > 2)
			flagArgument = arguments[2];

		if (!user->nickname.compare(nameArgument))
			return server.parseUserMode(user, flags, flagArgument);
		return server.parseChannelMode(user, nameArgument, flags, flagArgument);

	}

//////////////////////////////////////////////////////////////////////////////////


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

// --- command JOIN ---//
	Server::JoinCommand::JoinCommand()
		:	ChannelCommand("JOIN", false)
	{ }

	bool	Server::JoinCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		bool isOp = false;
		const std::string channelName = arguments[0];
		std::string password = "";
		if (arguments.size() > 1)
			password = arguments[1];
		Channel *channel = server.getChannel(channelName);

		if (!channel)	// if channel not present in serverChannels map
		{
			channel = new Channel(channelName);
			server.database->dataChannelsMap[channelName] = channel;	// Create the channel if it doesn't exist
			isOp = true;										// will set user as operator
			channel->addServer(&server);		// add server to the channel servers list
		}
		return channel->addClient(user, password, isOp);
	}

// --- command PART ---//
	Server::PartCommand::PartCommand()
		:	ChannelCommand("PART", true)
	{ }

	bool	Server::PartCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		const std::string channelName = arguments[0];
		Channel *channel = server.getChannel(channelName);

		if (!channel)
			return false;
		if (!user->isInChannel(channelName))
			return false;
		
		return channel->removeClient(user);
	}

// --- command NAMES ---//
	Server::NamesCommand::NamesCommand()
		:	ChannelCommand("NAMES", true)
	{ }

	bool	Server::NamesCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		(void)server;
		if (!arguments.size())
			return true;		// to manage by checking every channel

		const std::string channelName = arguments[0];
		Channel *channel = user->getChannelGlobal(channelName);

		if (!channel)
			return false;
		channel->displayNicknames();
		return true;
	}

// --- command LIST ---//
	Server::ListCommand::ListCommand()
		:	ChannelCommand("LIST", true)
	{ }

	bool	Server::ListCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		(void)server;
		const std::string channelName = arguments[0];

		if (user->clientChannels.find(channelName) == user->clientChannels.end())
			return false;
		user->leaveChannel(channelName);
		return true;
	}


// ============================================== //

// --- command MOTD ---//
	Server::MotdCommand::MotdCommand()
		:	Command("MOTD")
	{ }

	bool	Server::MotdCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		std::cout << user->username << " executes " << name << std::endl;

		*user << serializeReplyList<MotdStartReply, MotdReply, EndOfMotdReply>(
			"localhost", user->nickname, server.config["MOTD"], '\n', 80);

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
