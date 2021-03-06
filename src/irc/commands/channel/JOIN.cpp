#include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	void
	Server::JoinCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		if (arguments.empty())
		{
			*user << NeedMoreParamsError(gHostname, name);
			return;
		}

		if (!arguments[0].compare("0"))
		{
			for (AClient::channelMap::iterator it = user->channels.begin() ; !user->channels.empty() ; it = user->channels.begin())
			{
				*(it->second) << PartChannelMessage(user->nickname, it->second->name);
				server.database.delete_client_from_channel(it->second, user);
				// *user << PartChannelMessage(user->nickname, channelToLeave->name);
			}
			user->channels.clear();
			return;
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

			__Channel *channel = server.database.getChannel(channelName);

			if (user->channels.size() >= IRC_MAX_JOINED_CHANNEL)
			{
				*user << TooManyChannelsError(gHostname, channelName);
				return;
			}

			if (!channel ||
				!channel->isLocalChannelVisibleForClient(user))	// if channel not present in serverChannels map
			{
				try
				{
					channel = new __Channel(channelName);
					server.database.dataChannelsMap[channel->name] = channel;	// Create the channel if it doesn't exist
					isOp = true;										// will set user as operator
					if (channel->isNetworkUnmoderatedChannel())
						isOp = false;
					// channel->addServer(&server);		// add server to the channel servers list
					channel->setChannelModesOnCreation();
					channel->addClient(user, password, isOp, true);
				}
				catch(__Channel::InvalidChannelNameException const& e)
				{*user << NoSuchChannelError(gHostname, name);}
			}
			else
				channel->addClient(user, password, isOp, false);
		}
	}
}
