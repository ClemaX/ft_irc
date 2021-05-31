#include <irc/commands/ClientCommands.hpp>

#include <irc/commands/utils.hpp>

namespace NAMESPACE_IRC
{
	bool
	JoinCommand::
	payload(Database& database, AClient* const user, argumentList const& arguments) const
	{
		if (arguments.empty())
		{
			*user << NeedMoreParamsError(database.hostname, name);
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

			Channel *channel = database.getChannel(channelName);

			if (user->channels.size() >= IRC_MAX_JOINED_CHANNEL)
			{
				*user << TooManyChannelsError(gHostname, channelName);
				return false;
			}

			if (!channel || !channel->isLocalChannelVisibleForClient(user))	// if channel not present in serverChannels map
			{
				try
				{
					channel = new Channel(channelName);
					database.channels[channel->name] = channel;	// Create the channel if it doesn't exist
					isOp = true;										// will set user as operator
					if (channel->isNetworkUnmoderatedChannel())
						isOp = false;
					// TODO: Why are we adding server here
					//channel->addServer(&database);		// add database to the channel servers list
					channel->addClient(user, password, isOp);
				}
				catch(Channel::InvalidChannelNameException const& e)
				{*user << NoSuchChannelError(gHostname, name);}
			}
			else
				channel->addClient(user, password, isOp);
		}
		return true;
	}
}
