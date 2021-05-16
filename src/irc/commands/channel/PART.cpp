#include <irc/Server.hpp>

namespace irc
{
	Server::PartCommand::PartCommand()
		:	ChannelCommand("PART", true)
	{ }

	bool	Server::PartCommand::payload(Server& server, Client* user,
		argumentList const& arguments) const
	{
		if (!arguments.size())
		{
			*user << NeedMoreParamsError(gHostname, name);
			return false;
		}

		std::queue<std::string> channelsQueue;
		parseArgumentsQueue(arguments[0], channelsQueue);

		while (channelsQueue.size())
		{
			const std::string channelName = ft::strToLower(channelsQueue.front());
			channelsQueue.pop();

			Server::__Channel *channel = server.getChannel(channelName);

			if (!channel)
				*user << NoSuchChannelError(gHostname, channelName);
			else if (!user->isInChannel(channelName))
				*user << NotOnChannelError(gHostname, channelName);
			else
			{
				std::string leaveMessage = "";
				if (arguments.size() > 1)
					leaveMessage << user->nickname << " has left " << channelName << ": " << arguments[1];
				channel->removeClient(user, leaveMessage);
			}
		}
		return true;
	}
}
