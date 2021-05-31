#include <irc/commands/ClientCommands.hpp>

#include <irc/commands/utils.hpp>

namespace NAMESPACE_IRC
{
	bool
	ListCommand::
	payload(Database& database, AClient* const user, argumentList const& arguments) const
	{
		(void)database;
		if (!arguments.size())
			user->listAllChannelsListInfo(database);
		else
		{
			std::queue<std::string> channelsQueue;
			parseArgumentsQueue(arguments[0], channelsQueue);

			std::string target = "";
			if (arguments.size() > 1)
				target = arguments[1];

			while (channelsQueue.size())
			{
				const std::string channelName = ft::strToLower(channelsQueue.front());
				channelsQueue.pop();
				Channel	*channel = database.getVisibleChannel(user, channelName);
				user->listChannelInfo(channel);
			}
		}
		*user << EndOfListReply(gHostname);
		return true;
	}
}
