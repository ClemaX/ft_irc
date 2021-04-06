#include <IRCServer.hpp>

namespace irc
{

// ==========   CHANNEL MODES   ========== //

	bool	addChannelCreator(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isCreator(user))
			return false;
		return channel->addCreator(flagArguments);
	}

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


	bool	setChannelAnonymous(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.a = true;
std::cout << "channel " << channel->name << " has been set Anonymous!\n";
		return true;
	}

	bool	unsetChannelAnonymous(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.a = false;
std::cout << "channel " << channel->name << " has been set non Anonymous!\n";
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

	bool	setChannelQuiet(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.q = true;
std::cout << "channel " << channel->name << " has been set quiet!\n";
		return true;
	}

	bool	unsetChannelQuiet(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.q = false;
std::cout << "channel " << channel->name << " has been set non quiet!\n";
		return true;
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

	bool	setChannelReop(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.r = true;
std::cout << "channel " << channel->name << " has been set Reop!\n";
		return true;
	}

	bool	unsetChannelReop(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.r = false;
std::cout << "channel " << channel->name << " has been set non Reop!\n";
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

	bool	addChannelException(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
			return false;
		return channel->addException(flagArguments);
	}

	bool	removeChannelException(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
			return false;
		return channel->removeException(flagArguments);
	}

	bool	addChannelInviteList(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
			return false;
		return channel->addInviteList(flagArguments);
	}

	bool	removeChannelInviteList(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
			return false;
		return channel->removeInviteList(flagArguments);
	}

/// e

/// I



// --- parseChannelMode ---//
	bool	Server::parseChannelMode(Client *user, std::string const & channelName,
			std::string & flags, std::string & flagArguments)
	{
		char sign = flags[0];
		if (sign != '+' && sign != '-')
			return false;
		
		Channel *channel = user->getChannelGlobal(channelName);
		if (!channel)
			return false;
		
		flags.erase(0, 1);
		for (std::string::iterator it = flags.begin(); it != flags.end(); it++)
		{
			if (database->modeChannelFunctionsMap[sign].find(*it) == database->modeChannelFunctionsMap[sign].end())
				return false;
			database->modeChannelFunctionsMap[sign][*it](user, channel, flagArguments);
		}
		return true;
	}



// ==========   USER MODES   ========== //

	bool	setUserInvisible(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)channel;
		(void)flagArguments;
		user->clientModes.i = true;
std::cout << "user " << user->nickname << " has been set invisible!\n";
		return true;
	}

	bool	unsetUserInvisible(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)channel;
		(void)flagArguments;
		user->clientModes.i = false;
std::cout << "user " << user->nickname << " has been unset invisible!\n";
		return true;
	}

	bool	setUserServerNotice(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)channel;
		(void)flagArguments;
		user->clientModes.s = true;
std::cout << "user " << user->nickname << " has been marked for receipt of server notices!\n";
		return true;
	}

	bool	unsetUserServerNotice(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)channel;
		(void)flagArguments;
		user->clientModes.s = false;
std::cout << "user " << user->nickname << " has been unmarked for receipt of server notices!\n";
		return true;
	}

	bool	setUserWallops(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)channel;
		(void)flagArguments;
		user->clientModes.w = true;
std::cout << "user " << user->nickname << " has been set to receive wallops!\n";
		return true;
	}

	bool	unsetUserWallops(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)channel;
		(void)flagArguments;
		user->clientModes.w = false;
std::cout << "user " << user->nickname << " has been unset to receive wallops!\n";
		return true;
	}

		bool	setUserOperator(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)user;
		(void)channel;
		(void)flagArguments;
std::cout << "user " << user->nickname << " can't set himself as an operator!\n";
		return true;
	}

	bool	unsetUserOperator(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)channel;
		(void)flagArguments;
		user->clientModes.o = false;
std::cout << "user " << user->nickname << " has been unset as an operator!\n";
		return true;
	}




// --- parseUserMode ---//

	bool	Server::parseUserMode(Client *user,	std::string & flags, std::string & flagArguments)
	{
		char sign = flags[0];
		if (sign != '+' && sign != '-')
			return false;
		
		flags.erase(0, 1);
		for (std::string::iterator it = flags.begin(); it != flags.end(); it++)
		{
			if (database->modeUserFunctionsMap[sign].find(*it) == database->modeUserFunctionsMap[sign].end())
				return false;
			database->modeUserFunctionsMap[sign][*it](user, NULL, flagArguments);	// is it an error if there is a flagArgument ?
		}
		return true;
	}




}
