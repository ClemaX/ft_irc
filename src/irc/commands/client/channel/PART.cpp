#include <irc/commands/ClientCommands.hpp>

#include <irc/commands/utils.hpp>

namespace NAMESPACE_IRC
{
	bool
	PartCommand::
	payload(Database& database, AClient* const user,argumentList const& arguments) const
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

			Channel *channel = database.getChannel(channelName);

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
