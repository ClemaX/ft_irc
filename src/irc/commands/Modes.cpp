#include <irc/Server.hpp>

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
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+a", "");
		return true;
	}

	bool	unsetChannelAnonymous(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.a = false;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-a", "");
		return true;
	}


	bool	setChannelInviteOnly(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.i = true;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+i", "");
		return true;
	}

	bool	unsetChannelInviteOnly(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.i = false;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-i", "");
		return true;
	}

	bool	setChannelModerated(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.m = true;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+m", "");
		return true;
	}

	bool	unsetChannelModerated(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.m = false;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-m", "");
		return true;
	}

	bool	setChannelNoExternalMessage(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.n = true;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+n", "");
		return true;
	}

	bool	unsetChannelNoExternalMessage(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.n = false;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-n", "");
		return true;
	}

	bool	setChannelQuiet(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.q = true;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+q", "");
		return true;
	}

	bool	unsetChannelQuiet(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.q = false;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-q", "");
		return true;
	}

	bool	setChannelPrivate(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.p = true;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+p", "");
		return true;
	}

	bool	unsetChannelPrivate(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.p = false;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-p", "");
		return true;
	}

	bool	setChannelSecret(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.s = true;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+s", "");
		return true;
	}

	bool	unsetChannelSecret(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.s = false;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-s", "");
		return true;
	}

	bool	setChannelReop(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isCreator(user))
			return false;
		channel->channelModes.r = true;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+r", "");
		return true;
	}

	bool	unsetChannelReop(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isCreator(user))
			return false;
		channel->channelModes.r = false;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-r", "");
		return true;
	}

	bool	setChannelRestrictTopic(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.t = true;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+t", "");
		return true;
	}

	bool	unsetChannelRestrictTopic(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.t = false;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-t", "");
		return true;
	}




	bool	setChannelLimit(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
			return false;

		channel->channelModes.l = ft::atoi(flagArguments);	// error to manage if flagArgument is not valid ?
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+l", flagArguments);
		return true;
	}

	bool	unsetChannelLimit(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.l = 0;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-l", "");
		return true;
	}

	bool	addChannelKey(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.k = flagArguments;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+k", flagArguments);
		return true;
	}

	bool	removeChannelKey(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
			return false;
		channel->channelModes.k = "";
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-k", "");
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




// --- parseChannelMode ---//
	bool	Server::parseChannelMode(Client *user, std::string const & channelName,
			std::string & flags, std::string & flagArguments)
	{
		char sign = flags[0];
		if (sign != '+' && sign != '-')
		{
			*user << UModeUnkownFlagError(SERVER_NAME);
			return false;
		}

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
		std::string userMode = "";
		userMode.push_back(sign);
		if (sign != '+' && sign != '-')
		{
			*user << UModeUnkownFlagError(SERVER_NAME);
			return false;
		}

		flags.erase(0, 1);
		for (std::string::iterator it = flags.begin(); it != flags.end(); it++)
		{
			if (database->modeUserFunctionsMap[sign].find(*it) == database->modeUserFunctionsMap[sign].end())
				*user << UModeUnkownFlagError(SERVER_NAME);
			else
			{
				database->modeUserFunctionsMap[sign][*it](user, NULL, flagArguments);	// is it an error if there is a flagArgument ?
				userMode.replace(1, 1, 1, *it);
				*user << UModeIsReply(SERVER_NAME, userMode);	// what do we do if flag = 'o' or 's' ?
			}
		}
		return true;
	}




}
