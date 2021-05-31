#include <irc/commands/ClientCommands.hpp>

#include <irc/commands/utils.hpp>

namespace NAMESPACE_IRC
{
	bool
	KickCommand::
	payload(Database& database, AClient* const user, argumentList const& arguments) const
	{
		static_cast<void>(database);
		if (arguments.size() < 2)
		{
			*user << NeedMoreParamsError(gHostname, name);
			return false;
		}

		std::queue<std::string> channelsQueue;
		std::queue<std::string> usersQueue;

		parseArgumentsQueue(arguments[0], channelsQueue);
		parseArgumentsQueue(arguments[1], usersQueue);

		if (channelsQueue.size() != usersQueue.size() && channelsQueue.size() != 1)
		{
			*user << NeedMoreParamsError(gHostname, name);
			return false;
		}

		while (usersQueue.size())
		{
			const std::string channelName = ft::strToLower(channelsQueue.front());
			if (channelsQueue.size() > 1)
				channelsQueue.pop();
			const std::string clientNickname = usersQueue.front();
			usersQueue.pop();

			Channel *channel = database.getChannel(channelName);

			if (!channel || !channel->isVisibleForClient(user))
				*user << NoSuchChannelError(gHostname, channelName);
			else if (!user->isInChannel(channelName))
				*user << NotOnChannelError(gHostname, channelName);
			else if (!channel->isOperator(user))
				*user << ChannelOperatorPrivilegiesError(gHostname, channelName);
			else
			{
				AClient *victim = channel->getUser(clientNickname);
				if (!victim)
					*user << UserNotInChannelError(gHostname, clientNickname, channelName);
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
	}
}
