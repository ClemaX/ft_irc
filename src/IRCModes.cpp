#include <IRCServer.hpp>

namespace irc
{
	bool	addChannelOperator(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
			return false;
		return channel->addOperator(flagArguments);
	}

	bool	removeChannelOperator(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
			return false;
		return channel->removeOperator(flagArguments);
	}

	bool	setChannelPrivate(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.p = true;
std::cout << "channel " << channel->name << " has been set private!\n";
		return true;
	}

	bool	unsetChannelPrivate(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.p = false;
std::cout << "channel " << channel->name << " has been set non private!\n";
		return true;
	}

	bool	setChannelSecret(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.s = true;
std::cout << "channel " << channel->name << " has been set Secret!\n";
		return true;
	}

	bool	unsetChannelSecret(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.s = false;
std::cout << "channel " << channel->name << " has been set non Secret!\n";
		return true;
	}

	bool	setChannelInviteOnly(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.i = true;
std::cout << "channel " << channel->name << " has been set InviteOnly!\n";
		return true;
	}

	bool	unsetChannelInviteOnly(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.i = false;
std::cout << "channel " << channel->name << " has been set non InviteOnly!\n";
		return true;
	}

	bool	setChannelRestrictTopic(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.t = true;
std::cout << "channel " << channel->name << " has been set RestrictTopic!\n";
		return true;
	}

	bool	unsetChannelRestrictTopic(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.t = false;
std::cout << "channel " << channel->name << " has been set non RestrictTopic!\n";
		return true;
	}

	bool	setChannelNoExternalMessage(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.n = true;
std::cout << "channel " << channel->name << " has been set NoExternalMessage!\n";
		return true;
	}

	bool	unsetChannelNoExternalMessage(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.n = false;
std::cout << "channel " << channel->name << " has been set non NoExternalMessage!\n";
		return true;
	}

	bool	setChannelModerated(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.m = true;
std::cout << "channel " << channel->name << " has been set Moderated!\n";
		return true;
	}

	bool	unsetChannelModerated(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.m = false;
std::cout << "channel " << channel->name << " has been set non Moderated!\n";
		return true;
	}

	bool	setChannelLimit(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
			return false;
		
		channel->channelModes.l = ft::atoi(flagArguments);	// error to manage if flagArgument is not valid ?
std::cout << "channel " << channel->name << " limit has been set to " << channel->channelModes.l << "!\n";
		return true;
	}

	bool	unsetChannelLimit(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.l = 0;
std::cout << "channel " << channel->name << " limit has been set to " << channel->channelModes.l << "!\n";
		return true;
	}

	bool	addChannelBanned(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
			return false;
		return channel->addBanned(flagArguments);
	}

	bool	removeChannelBanned(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
			return false;
		return channel->removeBanned(flagArguments);
	}

	bool	addChannelVoice(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
			return false;
		return channel->addVoice(flagArguments);
	}

	bool	removeChannelVoice(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
			return false;
		return channel->removeVoice(flagArguments);
	}

	bool	addChannelKey(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.k = flagArguments;
std::cout << "channel " << channel->name << " key has been set to " << flagArguments << "!\n";
		return true;
	}

	bool	removeChannelKey(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.k = "";
std::cout << "channel " << channel->name << " key has been removed!\n";
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
