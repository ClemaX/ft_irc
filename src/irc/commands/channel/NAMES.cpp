#include <irc/Server.hpp>

namespace irc
{
	Server::NamesCommand::NamesCommand()
		:	ChannelCommand("NAMES", true)
	{ }

	bool	Server::NamesCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		if (!arguments.size())
		{
			IRCDatabase::databaseChannelsMap::iterator itb = server.database.dataChannelsMap.begin();
			IRCDatabase::databaseChannelsMap::iterator ite = server.database.dataChannelsMap.end();
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
			target = arguments[1];

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
	}
}