#include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	void
	Server::ListCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		(void)server;
		if (!arguments.size())
			user->listAllChannelsListInfo(server.database);
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
				// TODO: Shouldn't this be a database function?
				Server::__Channel *channel = user->getChannelGlobal(server.database, channelName);
				user->listChannelInfo(channel);
			}
		}
		*user << EndOfListReply(gHostname);
		return;
	}
}
