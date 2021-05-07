#include <irc/Server.hpp>

namespace irc
{
	SocketConnection const&	operator<<(SocketConnection const& client, IReply const& message)
	{
		client << message.serialize();

		return client;
	}


// --- command PASS --- //
	Server::PassCommand::PassCommand()
		:	Command("/pass")
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
		:	Command("/msg")
	{ }

	bool	Server::PRIVMSGCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		if (!arguments.size())
		{
			*user << NeedMoreParamsError(SERVER_NAME, name);
			return false;
		}
		std::string nameArgument = arguments[0];

		std::string message = "";
		if (arguments.size() > 1)
			message = arguments[1];

		Client *receiver = server.database->getClient(nameArgument);
		if (receiver)
			receiver->receiveMessage(user, message);	// check to add ? invisible ?
		else
		{
			Channel *channel = server.getChannel(nameArgument);
			if (channel)
				channel->receiveMessage(user, message);
		}
		return true;
	}

// ============================================== //
// ============================================== //



// ============================================== //
// ============   CHANNEL commands   ============ //
// ============================================== //

// --- command JOIN --- //
	Server::JoinCommand::JoinCommand()
		:	ChannelCommand("/join", false)
	{ }

	bool	Server::JoinCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		if (!arguments.size())
		{
			*user << NeedMoreParamsError(SERVER_NAME, name);
			return false;
		}

		if (!arguments[0].compare("0"))
		{
			user->leaveAllChannels();
			return true;
		}

		std::queue<std::string> channelsQueue;
		std::queue<std::string> passwordsQueue;

		parseArgumentsQueue(arguments[0], channelsQueue);
		if (arguments.size() > 1)
			parseArgumentsQueue(arguments[1], passwordsQueue);

		while (channelsQueue.size())
		{
			bool isOp = false;
			const std::string channelName = ft::strToLower(channelsQueue.front());
			channelsQueue.pop();
			std::string password = "";
			if (passwordsQueue.size())
			{
				password = passwordsQueue.front();
				passwordsQueue.pop();
			}

			Channel *channel = server.getChannel(channelName); // what happens if the server is private or secret ?

			if (user->clientChannels.size() >= IRC_MAX_JOINED_CHANNEL)
			{
				*user << TooManyChannelsError(SERVER_NAME, channelName);
				return false;
			}

			if (!channel ||
				!channel->isLocalChannelVisibleForClient(user))	// if channel not present in serverChannels map
			{
				try
				{
					channel = new Channel(channelName);
					server.database->dataChannelsMap[channel->name] = channel;	// Create the channel if it doesn't exist
					isOp = true;										// will set user as operator
					if (channel->isNetworkUnmoderatedChannel())
						isOp = false;
					channel->addServer(&server);		// add server to the channel servers list
					channel->addClient(user, password, isOp);
				}
				catch(Channel::InvalidChannelNameException const& e)
				{
					*user << NoSuchChannelError(SERVER_NAME, name);
					// return false;										//do we leave or check the next arguments ?
				}

			}
			else
				channel->addClient(user, password, isOp);
		}
		return true;

	// Errors not used yet
        //    ERR_BADCHANMASK
        //    ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE

	}


// --- command PART --- //
	Server::PartCommand::PartCommand()
		:	ChannelCommand("/part", true)
	{ }

	bool	Server::PartCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		if (!arguments.size())
		{
			*user << NeedMoreParamsError(SERVER_NAME, name);
			return false;
		}

		std::queue<std::string> channelsQueue;
		parseArgumentsQueue(arguments[0], channelsQueue);

		while (channelsQueue.size())
		{
			const std::string channelName = ft::strToLower(channelsQueue.front());
			channelsQueue.pop();

			Channel *channel = server.getChannel(channelName);

			if (!channel)
			{
				*user << NoSuchChannelError(SERVER_NAME, channelName);
				// return false;
			}
			else if (!user->isInChannel(channelName))
			{
				*user << NotOnChannelError(SERVER_NAME, channelName);
				// return false;
			}
			else
			{
				std::string leaveMessage = "";
				if (arguments.size() > 1)
					leaveMessage << user->nickname << " has left " << channelName << ": " << arguments[1];
				channel->removeClient(user, leaveMessage);
			}
		}

		return true;
		// Errors/replies not used yet
			// no reply ?
	}


// --- command MODE --- //
	Server::ModeCommand::ModeCommand()
		:	ChannelCommand("/mode", true)
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

			// RPL_UNIQOPIS

	}


// --- command TOPIC --- //
	Server::TopicCommand::TopicCommand()
		:	ChannelCommand("/topic", true)
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


// --- command NAMES --- //
	Server::NamesCommand::NamesCommand()
		:	ChannelCommand("/names", true)
	{ }

	bool	Server::NamesCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		if (!arguments.size())
		{
			IRCDatabase::databaseChannelsMap::iterator itb = server.database->dataChannelsMap.begin();
			IRCDatabase::databaseChannelsMap::iterator ite = server.database->dataChannelsMap.end();
			while (itb != ite)
			{
				if (itb->second->isVisibleForClient(user))
				{
					*user << ChannelNamesReply(SERVER_NAME, itb->second);
					*user << EndOfNamesReply(SERVER_NAME, itb->first);
				}
				itb++;
			}
			return true;
		}

		std::queue<std::string> channelsQueue;
		parseArgumentsQueue(arguments[0], channelsQueue);

		std::string target = "";
		if (arguments.size() > 1)
			target = arguments[1];				// need to use target

		while (channelsQueue.size())
		{
			const std::string channelName = ft::strToLower(channelsQueue.front());
			channelsQueue.pop();
			Channel *channel = user->getChannelGlobal(channelName);

			if (channel && channel->isVisibleForClient(user))
			{
				*user << ChannelNamesReply(SERVER_NAME, channel);
				*user << EndOfNamesReply(SERVER_NAME, channelName);
			}
		}
		return true;

		// Errors/replies not used yet
			// ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
	}


// --- command LIST --- //
	Server::ListCommand::ListCommand()
		:	ChannelCommand("/list", true)
	{ }

	bool	Server::ListCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		(void)server;
		if (!arguments.size())
			user->listAllChannelsListInfo();
		else
		{
			std::queue<std::string> channelsQueue;
			parseArgumentsQueue(arguments[0], channelsQueue);

			std::string target = "";
			if (arguments.size() > 1)
				target = arguments[1];				// need to use target

			while (channelsQueue.size())
			{
				const std::string channelName = ft::strToLower(channelsQueue.front());
				channelsQueue.pop();
				Channel *channel = user->getChannelGlobal(channelName);
				user->listChannelInfo(channel);						// need to be adjusted ?
			}
		}
		*user << EndOfListReply(SERVER_NAME);
		return true;

		// Errors/replies not used yet
			// ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
	}


// --- command INVITE --- //
	Server::InviteCommand::InviteCommand()
		:	ChannelCommand("/invite", true)
	{ }

	bool	Server::InviteCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		if (arguments.size() < 2)
		{
			*user <<  NeedMoreParamsError(SERVER_NAME, name);
			return false;
		}
		std::string const nickname = arguments[0];
		std::string const channelName = arguments[1];

		Client *client = server.database->getClient(nickname);
		if (!client)
		{
			*user << NoSuchNicknameError(SERVER_NAME, nickname);
			return false;
		}
		Channel *channel = server.database->getChannel(channelName);
		if (!channel)
		{
			*user << InvitingReply(SERVER_NAME, channelName, nickname);
			*client << InviteChannelMessage(user->nickname, channelName);
			return true;
		}

		if (!user->isInChannel(channelName))
		{
			*user << NotOnChannelError(SERVER_NAME, channelName);
			return false;
		}
		if ((channel->channelModes.binMode & M_i) && !channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channelName);
			return false;
		}
		if (client->isInChannel(channelName))
		{
			*user << UserOnChannelError(SERVER_NAME, nickname, channelName);
			return false;
		}
		if (channel->channelModes.binMode & M_i)
			channel->addInviteList(nickname);			// Do we need to set a timer ?
		*client << InviteChannelMessage(user->nickname, channelName);
		*user << InvitingReply(SERVER_NAME, channelName, nickname);
		return true;

		// Errors/replies not used yet
			// RPL_AWAY
	}


// --- command KICK --- //
	Server::KickCommand::KickCommand()
		:	ChannelCommand("/kick", true)
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

		std::queue<std::string> channelsQueue;
		std::queue<std::string> usersQueue;

		parseArgumentsQueue(arguments[0], channelsQueue);
		parseArgumentsQueue(arguments[1], usersQueue);

		if (channelsQueue.size() != usersQueue.size() && channelsQueue.size() != 1)
		{
			*user << NeedMoreParamsError(SERVER_NAME, name);
			return false;
		}

		while (usersQueue.size())
		{
			const std::string channelName = ft::strToLower(channelsQueue.front());
			if (channelsQueue.size() > 1)
				channelsQueue.pop();
			const std::string clientNickname = usersQueue.front();
			usersQueue.pop();

			Channel *channel = user->getChannelGlobal(channelName);			// need to check privacy ?
			if (!channel || !channel->isVisibleForClient(user))
			{
				*user << NoSuchChannelError(SERVER_NAME, channelName);
				// return false;
			}
			else if (!user->isInChannel(channelName))
			{
				*user << NotOnChannelError(SERVER_NAME, channelName);
				// return false;
			}
			else if (!channel->isOperator(user))
			{
				*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channelName);
				// return false;
			}
			else
			{
				Client *victim = channel->getUser(clientNickname);
				if (!victim)
				{
					*user << UserNotInChannelError(SERVER_NAME, clientNickname, channelName);
					// return false;
				}
				else
				{
					std::string comment = "";
					comment << clientNickname << " has been kicked from " << channelName;
					if (arguments.size() > 2)
						comment << ": " << arguments[2];
					channel->removeClient(victim, comment);
				}
			}
		}

		return true;

		// Errors not used yet
			// ERR_BADCHANMASK
	}


// ============================================== //
// ============================================== //


// ============================================== //
// ============     USER queries     ============ //
// ============================================== //

// --- WHO query --- //

	Server::WhoQuery::WhoQuery()
		:	Command("/who")
	{ }

	bool	Server::WhoQuery::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		std::string mask = "";
		if (!arguments.size() || !arguments[0].compare("0") || !arguments[0].compare("*"))
			user->listAllVisibleUsersWhoQueryInfo();
		else
		{
			mask = arguments[0];
			int	opFlag = 0;
			if (arguments.size() > 1 && !arguments[1].compare("o"))
				opFlag = 1;

			Channel *channel = server.database->getChannel(mask);
			if (channel)
				user->listChannelWhoQueryInfo(channel, opFlag);
			else
				user->matchMaskWhoQueryInfo(mask); // function to complete with match with users' server
		}
		*user << EndOfWhoReply(SERVER_NAME, mask);

		return true;

		// Errors/replies not used yet
			// ERR_NOSUCHSERVER

	}

// --- NICK --- //

	Server::NickCommand::NickCommand()
	: Command("/nick")
	{ }

	bool
	Server::NamesCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		// TO DO: Did i handle the errors well ?
		// TO DO: DO i have to delete something in some database ?
		// TO DO: What happens if an user alreaddy has a nick and uses the NICK cmd
		//		with only one argument ? Should i handle that too ?
		// TO DO: Did i handle well the collisions ?
		// TO DO: Does this function need to write in some stream ?
		// TO DO: What do when arguments.at(0) == arguments.at(1) ?

		// 0 < arguments.size() < 2
		if (arguments.empty() || arguments.size() > 2
		// nickname to change is not user's nick
		|| (arguments.size() - 2UL == 0UL && user->nickname != arguments.at(0)))
			return (false);

		// <NICK> <nickname> [ <new_nickname> ]
		const std::string& nick = arguments.size() - 1UL == 0UL
		? arguments.at(0) : arguments.at(1);

		// Check for collisions
		if (server.database->getClient(nick) == 0)
			return (false);

		// Edit nickname
		user->nickname = nick;
		return (true);
	}


// ============================================== //
// ============================================== //


// --- command MOTD --- //
	Server::MotdCommand::MotdCommand()
		:	Command("/motd")
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
