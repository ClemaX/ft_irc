#include <irc/Server.hpp>

namespace irc
{
	Server::PartCommand::PartCommand()
		:	ChannelCommand("PART", true)
	{ }

	bool	Server::PartCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		if (!arguments.size())
		{
			*user << NeedMoreParamsError(SERVER_NAME, name);
			return false;
		}

		std::queue<std::string> channelsQueue;
		parseArgumentsQueue(arguments[0], channelsQueue);

		while (channelsQueue.size())
		{
			const std::string channelName = ft::strToLower(channelsQueue.front());
			channelsQueue.pop();

			Channel *channel = server.getChannel(channelName);

			if (!channel)
				*user << NoSuchChannelError(SERVER_NAME, channelName);
			else if (!user->isInChannel(channelName))
				*user << NotOnChannelError(SERVER_NAME, channelName);
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
