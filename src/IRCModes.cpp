#include <IRCServer.hpp>

namespace irc
{


// --- command MODE ---//
	bool	parseChannelMode(Client *user, std::string const & channelName,
			std::string const & flags, std::string const & flagArguments)
	{
		(void)flags;
		(void)flagArguments;

		Channel *channel = user->getChannelGlobal(channelName);
		if (!channel)
			return false;
		
		// now we have to check +/-, flags and arguments

		return true;
	}



}
