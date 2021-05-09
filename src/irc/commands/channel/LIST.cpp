#include <irc/Server.hpp>

namespace irc
{
	Server::ListCommand::ListCommand()
		:	ChannelCommand("/list", true)
	{ }

	bool	Server::ListCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		(void)server;
		if (!arguments.size())
			user->listAllChannelsListInfo();
		else
		{
			std::queue<std::string> channelsQueue;
			parseArgumentsQueue(arguments[0], channelsQueue);

			std::string target = "";
			if (arguments.size() > 1)
				target = arguments[1];				// need to use target

			while (channelsQueue.size())
			{
				const std::string channelName = ft::strToLower(channelsQueue.front());
				channelsQueue.pop();
				Channel *channel = user->getChannelGlobal(channelName);
				user->listChannelInfo(channel);						// need to be adjusted ?
			}
		}
		*user << EndOfListReply(SERVER_NAME);
		return true;

		// Errors/replies not used yet
			// ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
	}
}
