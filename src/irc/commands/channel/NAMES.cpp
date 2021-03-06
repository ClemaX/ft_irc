#include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	void
	Server::NamesCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		if (!arguments.size())
		{
			IRCDatabase::databaseChannelsMap::iterator itb = server.database.dataChannelsMap.begin();
			IRCDatabase::databaseChannelsMap::iterator ite = server.database.dataChannelsMap.end();
			while (itb != ite)
			{
				if (itb->second->isVisibleForClient(user))
				{
					*user << ChannelNamesReply(gHostname, itb->second);
					*user << EndOfNamesReply(gHostname, itb->first);
				}
				itb++;
			}
			return;
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
			Server::__Channel *channel = user->getChannelGlobal(server.database, channelName);

			if (channel && channel->isVisibleForClient(user))
			{
				*user << ChannelNamesReply(gHostname, channel);
				*user << EndOfNamesReply(gHostname, channelName);
			}
		}
		return;
	}
}
