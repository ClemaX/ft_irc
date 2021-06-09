#include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	void
	Server::PartCommand::
	payload(Server& server, AClient* const user,argumentList const& arguments) const
	{
		if (!arguments.size())
		{
			*user << NeedMoreParamsError(gHostname, name);
			return;
		}

		std::queue<std::string> channelsQueue;
		parseArgumentsQueue(arguments[0], channelsQueue);

		while (channelsQueue.size())
		{
			const std::string channelName = ft::strToLower(channelsQueue.front());
			channelsQueue.pop();

			Server::__Channel *channel = server.database.getChannel(channelName);

			if (!channel)
				*user << NoSuchChannelError(gHostname, channelName);
			else if (!user->isInChannel(channelName))
				*user << NotOnChannelError(gHostname, channelName);
			else
			{
				std::string leaveMessage = "";
				if (arguments.size() > 1)
					leaveMessage << arguments[1];
				*channel << PartChannelMessage(user->nickname, channelName, leaveMessage);
				server.database.delete_client_from_channel(channel, user);
				// *user << PartChannelMessage(user->nickname, channelName, leaveMessage);
			}
		}
	}
}
