#include <irc/Server.hpp>

namespace irc
{
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
}
