#include <irc/Server.hpp>

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
			*user << NeedMoreParamsError(SERVER_NAME, name); // << user->nickname << ft::itoa(_ERR_NEEDMOREPARAMS);
			return false;
		}
		std::cout << "Setting password '" << arguments[0] << "'" << std::endl;
		return true;
	}



// ============================================== //
// ============   Private Messages   ============ //
// ============================================== //

	Server::PRIVMSGCommand::PRIVMSGCommand()
		:	Command("PRIVMSG")
	{ }

	bool	Server::PRIVMSGCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		if (!arguments.size())
		{
			*user << NeedMoreParamsError(SERVER_NAME, name);
			return false;
		}
		std::string receiverNickname = arguments[0];
		IRCDatabase::databaseClientsMap::iterator it = server.database->dataClientsMap.find(receiverNickname);
		if (it == server.database->dataClientsMap.end())
			return false;
		std::string message = "";
		if (arguments.size() > 1)
			message = arguments[1];
		*(it->second) << PrivateMessage(user->nickname, message);
		return true;
	}

// ============================================== //
// ============================================== //



// ============================================== //
// ============   CHANNEL commands   ============ //
// ============================================== //

// --- command KICK ---//
	Server::KickCommand::KickCommand()
		:	ChannelCommand("KICK", true)
	{ }

	bool	Server::KickCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		(void)server;
		if (arguments.size() < 2)
		{
			*user << NeedMoreParamsError(SERVER_NAME, name);
			return false;
		}
		std::string channelName = ft::strToLower(arguments[0]);
		std::string clientNickname = arguments[1]; // do we check the username ? Nickname ?
		
		Channel *channel = user->getChannelGlobal(channelName);			// need to check privacy ?
		if (!channel || !channel->isVisible(user))
		{
			*user << NoSuchChannelError(SERVER_NAME, channelName);
			return false;
		}
		if (!user->isInChannel(channelName))
		{
			*user << NotOnChannelError(SERVER_NAME, channelName);
			return false;
		}
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channelName);
			return false;
		}
		Client *victim = channel->getUser(clientNickname); // do we check the username ? Nickname ?
		if (!victim)
		{
			*user << UserNotInChannelError(SERVER_NAME, clientNickname, channelName);
			return false;
		}
		victim->leaveChannel(channelName);

		if (arguments.size() > 2 && arguments[2][0] == IRC_MESSAGE_PREFIX_PREFIX)
		{
			std::string comment = arguments[2];
			comment.erase(0,1);
			std::cout << "Reason: \"" << comment << "\"\n";
		}
		return true;

		// Errors not used yet
			// ERR_BADCHANMASK                 
	}

// --- command MODE ---//
	Server::ModeCommand::ModeCommand()
		:	ChannelCommand("MODE", true)
	{ }

	bool	Server::ModeCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		(void)server;
		if (arguments.size() < 2)
		{
			*user << NeedMoreParamsError(SERVER_NAME, name);
			return false;
		}

		std::string nameArgument = arguments[0];
		std::string flags = arguments[1];
		if (!flags.size())
			return false;

		std::string	flagArgument = "";
		if (arguments.size() > 2)
			flagArgument = arguments[2];

		if (!server.database->getClient(nameArgument))
			return server.parseChannelMode(user, nameArgument, flags, flagArgument);		
		if (!user->nickname.compare(nameArgument))
			return server.parseUserMode(user, flags, flagArgument);
		*user << UsersDontMatchError(SERVER_NAME);
		return false;

		// Errors/replies not used yet - user

		// Errors/replies not used yet - channel
			// ERR_KEYSET
			// ERR_NOCHANMODES

			// RPL_UNIQOPIS

	}


// --- command INVITE ---//
	Server::InviteCommand::InviteCommand()		// Not done yet --> How does it work ? //
		:	ChannelCommand("INVITE", true)
	{ }

	bool	Server::InviteCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		(void)server;
		(void)arguments;
		std::cout << user->username << " executes " << name << std::endl;
		return false;

		// Errors/replies not used yet
			// ERR_NEEDMOREPARAMS	ERR_NOSUCHNICK
			// ERR_NOTONCHANNEL		ERR_USERONCHANNEL
			// ERR_CHANOPRIVSNE		
			// RPL_INVITING    		RPL_AWAY
	}

// --- command TOPIC ---//
	Server::TopicCommand::TopicCommand()
		:	ChannelCommand("TOPIC", true)
	{ }

	bool	Server::TopicCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		(void)server;
		if (!arguments.size())
		{
			*user <<  NeedMoreParamsError(SERVER_NAME, name);
			return false;
		}

		const std::string channelName = ft::strToLower(arguments[0]);
		Channel	*channel = user->getChannel(channelName);

		if (!channel)
		{
			*user <<  NotOnChannelError(SERVER_NAME, channelName);
			return false;
		}
		else if (arguments.size() == 1)
		{
			const std::string	topic = channel->getTopic();
			if (!topic.compare(""))
				*user << NoTopicReply(SERVER_NAME, channelName);
			else
				*user << TopicReply(SERVER_NAME, channelName, topic);
			return true;
		}
		else if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channelName);
			return false;
		}
		else
		{
			const std::string newTopic = arguments[1];
			channel->setTopic(newTopic);
			*user << TopicReply(SERVER_NAME, channelName, newTopic);
		}
		return true;

		// Errors/replies not used yet
			// ERR_NOCHANMODES
	}

// --- command JOIN ---//
	Server::JoinCommand::JoinCommand()
		:	ChannelCommand("JOIN", false)
	{ }

	bool	Server::JoinCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		if (!arguments.size())
		{
			*user << NeedMoreParamsError(SERVER_NAME, name);
			return false;
		}
		bool isOp = false;
		const std::string channelName = ft::strToLower(arguments[0]);
		std::string password = "";
		if (arguments.size() > 1)
			password = arguments[1];
		Channel *channel = server.getChannel(channelName); // what happens if the server is private or secret ?

		if (user->clientChannels.size() >= IRC_MAX_JOINED_CHANNEL)
		{
			*user << TooManyChannelsError(SERVER_NAME, channelName);
			return false;
		}

		if (!channel)	// if channel not present in serverChannels map
		{
			try{channel = new Channel(channelName);}
			catch(Channel::InvalidChannelNameException const& e)
			{
				*user << NoSuchChannelError(SERVER_NAME, name);
				return false;
			}
			server.database->dataChannelsMap[channelName] = channel;	// Create the channel if it doesn't exist
			isOp = true;										// will set user as operator
			channel->addServer(&server);		// add server to the channel servers list
		}
		return channel->addClient(user, password, isOp);

	// Errors not used yet 
        //    ERR_BADCHANMASK
        //    ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE

	}

// --- command PART ---//
	Server::PartCommand::PartCommand()
		:	ChannelCommand("PART", true)
	{ }

	bool	Server::PartCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		if (!arguments.size())
		{
			*user << NeedMoreParamsError(SERVER_NAME, name);
			return false;
		}

		const std::string channelName = ft::strToLower(arguments[0]);
		Channel *channel = server.getChannel(channelName);

		if (!channel)
		{
			*user << NoSuchChannelError(SERVER_NAME, channelName);
			return false;
		}
		if (!user->isInChannel(channelName))
		{
			*user << NotOnChannelError(SERVER_NAME, channelName);
			return false;
		}
		return channel->removeClient(user);

		// Errors/replies not used yet
			// no reply ?
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
		{
			
			return true;		// to manage by checking every channel seen by user
		}

		const std::string channelName = ft::strToLower(arguments[0]);
		Channel *channel = user->getChannelGlobal(channelName);			// need to check privacy ?

		if (!channel || !channel->isVisible(user))
			return false;
		*user << ChannelNamesReply(SERVER_NAME, channel);
		*user << EndOfNamesReply(SERVER_NAME, channelName);
		return true;

		// Errors/replies not used yet
			// ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
	}

// --- command LIST ---//
	Server::ListCommand::ListCommand()
		:	ChannelCommand("LIST", true)
	{ }

	bool	Server::ListCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		(void)server;
		if (!arguments.size())
			user->listAllChannelsInfo();
		else
		{
			const std::string channelName = ft::strToLower(arguments[0]);
			Channel *channel = user->getChannelGlobal(channelName);
			user->listChannelInfo(channel);						// need to be adjusted ?
		}
		*user << EndOfListReply(SERVER_NAME);
		return true;

		// Errors/replies not used yet
			// ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
	}

// ============================================== //
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
			SERVER_NAME, user->nickname, server.config["MOTD"], '\n', 80);

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
