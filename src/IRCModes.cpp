#include <IRCServer.hpp>
#include <IRCDatabase.hpp>

namespace irc
{


	bool	setChannelPrivate(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
std::cout << "channel " << channel->name << " has been set private!\n";
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.p = true;
		return true;
	}

	bool	setChannelNonPrivate(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
std::cout << "channel " << channel->name << " has been set non private!\n";
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.p = false;
		return true;
	}

	bool	setChannelSecret(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
std::cout << "channel " << channel->name << " has been set Secret!\n";
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.s = true;
		return true;
	}

	bool	setChannelNonSecret(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
std::cout << "channel " << channel->name << " has been set non Secret!\n";
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.s = false;
		return true;
	}




// --- command MODE ---//
	bool	Server::parseChannelMode(Client *user, std::string const & channelName,
			std::string & flags, std::string & flagArguments)
	{
		(void)flags;
		(void)flagArguments;

// std::cout << "flags: '" << flags << "'\nargs:'" << flagArguments << "'\n";

		char sign = flags[0];
		if (sign != '+' && sign != '-')
			return false;
		
		Channel *channel = user->getChannelGlobal(channelName);
		if (!channel)
			return false;
		
		flags.erase(0, 1);
		for (std::string::iterator it = flags.begin(); it != flags.end(); it++)
		{
			if (database->modeFunctionsMap[sign].find(*it) == database->modeFunctionsMap[sign].end())
				return false;
			database->modeFunctionsMap[sign][*it](user, channel, flagArguments);
		}

		return true;
	}




}
