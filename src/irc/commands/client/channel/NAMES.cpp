#include <irc/commands/ClientCommands.hpp>

#include <irc/commands/utils.hpp>

namespace NAMESPACE_IRC
{
	bool
	NamesCommand::
	payload(Database& database, AClient* const user, argumentList const& arguments) const
	{
		if (!arguments.size())
		{
			Database::channelMap::iterator itb = database.channels.begin();
			Database::channelMap::iterator ite = database.channels.end();
			while (itb != ite)
			{
				if (itb->second->isVisibleForClient(user))
				{
					*user << ChannelNamesReply(gHostname, itb->second);
					// TODO: EndOfNamesReply should be after the loop (unique)
					*user << EndOfNamesReply(gHostname, itb->first);
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

			Channel *channel = database.getVisibleChannel(user, channelName);

			if (channel)
			{
				*user << ChannelNamesReply(gHostname, channel);
			// TODO: EndOfNamesReply should be after the loop (unique)
				*user << EndOfNamesReply(gHostname, channelName);
			}
		}
		return true;
	}
}
