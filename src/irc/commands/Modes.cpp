#include <irc/Server.hpp>

namespace irc
{

// ==========   CHANNEL MODES   ========== //

	bool	addChannelCreator(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isCreator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		return channel->addCreator(flagArguments);
	}

	bool	addChannelOperator(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		return channel->addOperator(flagArguments);
	}

	bool	removeChannelOperator(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		return channel->removeOperator(flagArguments);
	}

	bool	addChannelVoice(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		return channel->addVoice(flagArguments);
	}

	bool	removeChannelVoice(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		return channel->removeVoice(flagArguments);
	}


	bool	setChannelAnonymous(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.binMode |= M_a;
		// channel->channelModes.a = true;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+a", "");
		return true;
	}

	bool	unsetChannelAnonymous(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.binMode &= ~M_a;
		// channel->channelModes.a = false;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-a", "");
		return true;
	}


	bool	setChannelInviteOnly(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.binMode |= M_i;
		// channel->channelModes.i = true;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+i", "");
		return true;
	}

	bool	unsetChannelInviteOnly(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.binMode &= ~M_i;
		// channel->channelModes.i = false;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-i", "");
		return true;
	}

	bool	setChannelModerated(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.binMode |= M_m;
		// channel->channelModes.m = true;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+m", "");
		return true;
	}

	bool	unsetChannelModerated(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.binMode &= ~M_m;
		// channel->channelModes.m = false;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-m", "");
		return true;
	}

	bool	setChannelNoExternalMessage(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.binMode |= M_n;
		// channel->channelModes.n = true;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+n", "");
		return true;
	}

	bool	unsetChannelNoExternalMessage(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.binMode &= ~M_n;
		// channel->channelModes.n = false;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-n", "");
		return true;
	}

	bool	setChannelQuiet(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.binMode |= M_q;
		// channel->channelModes.q = true;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+q", "");
		return true;
	}

	bool	unsetChannelQuiet(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.binMode &= ~M_q;
		// channel->channelModes.q = false;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-q", "");
		return true;
	}

	bool	setChannelPrivate(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.binMode |= M_p;
		// channel->channelModes.p = true;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+p", "");
		return true;
	}

	bool	unsetChannelPrivate(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.binMode &= ~M_p;
		// channel->channelModes.p = false;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-p", "");
		return true;
	}

	bool	setChannelSecret(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.binMode |= M_s;
		// channel->channelModes.s = true;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+s", "");
		return true;
	}

	bool	unsetChannelSecret(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.binMode &= ~M_s;
		// channel->channelModes.s = false;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-s", "");
		return true;
	}

	bool	setChannelReop(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isCreator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.binMode |= M_r;
		// channel->channelModes.r = true;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+r", "");
		return true;
	}

	bool	unsetChannelReop(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isCreator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.binMode &= ~M_r;
		// channel->channelModes.r = false;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-r", "");
		return true;
	}

	bool	setChannelRestrictTopic(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.binMode |= M_t;
		// channel->channelModes.t = true;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+t", "");
		return true;
	}

	bool	unsetChannelRestrictTopic(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.binMode &= ~M_t;
		// channel->channelModes.t = false;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-t", "");
		return true;
	}




	bool	setChannelLimit(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}

		channel->channelModes.l = ft::atoi(flagArguments);	// error to manage if flagArgument is not valid ?
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+l", flagArguments);
		return true;
	}

	bool	unsetChannelLimit(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.l = 0;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-l", "");
		return true;
	}

	bool	addChannelKey(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.k = flagArguments;
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "+k", flagArguments);
		return true;
	}

	bool	removeChannelKey(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		channel->channelModes.k = "";
		*channel << ChannelModeIsReply(SERVER_NAME, channel->name, "-k", "");
		return true;
	}




	bool	addChannelBanned(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!flagArguments.size())
		{
			for (Channel::channelNicknameMap::iterator it = channel->channelModes.b.begin() ; it != channel->channelModes.b.end() ; it++)
				*user << BanListReply(SERVER_NAME, channel->name, "+", it->first);
			*user << EndOfBanListReply(SERVER_NAME, channel->name);
			return true;
		}
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		return channel->addBanned(flagArguments);
	}

	bool	removeChannelBanned(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!flagArguments.size())
		{
			for (Channel::channelNicknameMap::iterator it = channel->channelModes.b.begin() ; it != channel->channelModes.b.end() ; it++)
				*user << BanListReply(SERVER_NAME, channel->name, "+", it->first);
			*user << EndOfBanListReply(SERVER_NAME, channel->name);
			return true;
		}
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		return channel->removeBanned(flagArguments);
	}

	bool	addChannelException(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!flagArguments.size())
		{
			for (Channel::channelNicknameMap::iterator it = channel->channelModes.e.begin() ; it != channel->channelModes.e.end() ; it++)
				*user << ExceptionListReply(SERVER_NAME, channel->name, "+", it->first);
			*user << EndOfExceptionListReply(SERVER_NAME, channel->name);
			return true;
		}
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		return channel->addException(flagArguments);
	}

	bool	removeChannelException(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!flagArguments.size())
		{
			for (Channel::channelNicknameMap::iterator it = channel->channelModes.e.begin() ; it != channel->channelModes.e.end() ; it++)
				*user << ExceptionListReply(SERVER_NAME, channel->name, "+", it->first);
			*user << EndOfExceptionListReply(SERVER_NAME, channel->name);
			return true;
		}
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		return channel->removeException(flagArguments);
	}

	bool	addChannelInviteList(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!flagArguments.size())
		{
			for (Channel::channelNicknameMap::iterator it = channel->channelModes.I.begin() ; it != channel->channelModes.I.end() ; it++)
				*user << InviteListReply(SERVER_NAME, channel->name, "+", it->first);
			*user << EndOfInviteListReply(SERVER_NAME, channel->name);
			return true;
		}
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
		return channel->addInviteList(flagArguments);
	}

	bool	removeChannelInviteList(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!flagArguments.size())
		{
			for (Channel::channelNicknameMap::iterator it = channel->channelModes.I.begin() ; it != channel->channelModes.I.end() ; it++)
				*user << InviteListReply(SERVER_NAME, channel->name, "+", it->first);
			*user << EndOfInviteListReply(SERVER_NAME, channel->name);
			return true;
		}
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channel->name);
			return false;
		}
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
		*user << UModeIsReply(SERVER_NAME, "+i");	// send reply to user or server ? same for the functions below
		return true;
	}

	bool	unsetUserInvisible(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)channel;
		(void)flagArguments;
		user->clientModes.i = false;
		*user << UModeIsReply(SERVER_NAME, "-i");
		return true;
	}

	bool	setUserServerNotice(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)channel;
		(void)flagArguments;
		user->clientModes.s = true;
		*user << UModeIsReply(SERVER_NAME, "+s");
		return true;
	}

	bool	unsetUserServerNotice(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)channel;
		(void)flagArguments;
		user->clientModes.s = false;
		*user << UModeIsReply(SERVER_NAME, "-s");
		return true;
	}

	bool	setUserWallops(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)channel;
		(void)flagArguments;
		user->clientModes.w = true;
		*user << UModeIsReply(SERVER_NAME, "+w");
		return true;
	}

	bool	unsetUserWallops(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)channel;
		(void)flagArguments;
		user->clientModes.w = false;
		*user << UModeIsReply(SERVER_NAME, "-w");
		return true;
	}

		bool	setUserOperator(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)user;
		(void)channel;
		(void)flagArguments;
		*user << UModeIsReply(SERVER_NAME, "+o");
		return true;
	}

	bool	unsetUserOperator(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)channel;
		(void)flagArguments;
		user->clientModes.o = false;
		*user << UModeIsReply(SERVER_NAME, "-o");
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
