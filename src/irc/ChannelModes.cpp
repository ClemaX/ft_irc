#include <irc/Server.hpp>

namespace irc
{

// ==========   CHANNEL MODES   ========== //

	bool	addChannelCreator(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isCreator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		return channel->addCreator(flagArguments);
	}

	bool	addChannelOperator(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		return channel->addOperator(flagArguments);
	}

	bool	removeChannelOperator(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		return channel->removeOperator(flagArguments);
	}

	bool	addChannelVoice(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		return channel->addVoice(flagArguments);
	}

	bool	removeChannelVoice(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		return channel->removeVoice(flagArguments);
	}


	bool	setChannelAnonymous(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.binMode |= M_a;
		*channel << ChannelModeIsReply(gHostname, channel->name, "+a", "");
		return true;
	}

	bool	unsetChannelAnonymous(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.binMode &= ~M_a;
		*channel << ChannelModeIsReply(gHostname, channel->name, "-a", "");
		return true;
	}


	bool	setChannelInviteOnly(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.binMode |= M_i;
		*channel << ChannelModeIsReply(gHostname, channel->name, "+i", "");
		return true;
	}

	bool	unsetChannelInviteOnly(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.binMode &= ~M_i;
		*channel << ChannelModeIsReply(gHostname, channel->name, "-i", "");
		return true;
	}

	bool	setChannelModerated(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.binMode |= M_m;
		*channel << ChannelModeIsReply(gHostname, channel->name, "+m", "");
		return true;
	}

	bool	unsetChannelModerated(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.binMode &= ~M_m;
		*channel << ChannelModeIsReply(gHostname, channel->name, "-m", "");
		return true;
	}

	bool	setChannelNoExternalMessage(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.binMode |= M_n;
		*channel << ChannelModeIsReply(gHostname, channel->name, "+n", "");
		return true;
	}

	bool	unsetChannelNoExternalMessage(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.binMode &= ~M_n;
		*channel << ChannelModeIsReply(gHostname, channel->name, "-n", "");
		return true;
	}

	bool	setChannelQuiet(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.binMode |= M_q;
		*channel << ChannelModeIsReply(gHostname, channel->name, "+q", "");
		return true;
	}

	bool	unsetChannelQuiet(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.binMode &= ~M_q;
		*channel << ChannelModeIsReply(gHostname, channel->name, "-q", "");
		return true;
	}

	bool	setChannelPrivate(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.binMode |= M_p;
		*channel << ChannelModeIsReply(gHostname, channel->name, "+p", "");
		return true;
	}

	bool	unsetChannelPrivate(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.binMode &= ~M_p;
		*channel << ChannelModeIsReply(gHostname, channel->name, "-p", "");
		return true;
	}

	bool	setChannelSecret(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.binMode |= M_s;
		*channel << ChannelModeIsReply(gHostname, channel->name, "+s", "");
		return true;
	}

	bool	unsetChannelSecret(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.binMode &= ~M_s;
		*channel << ChannelModeIsReply(gHostname, channel->name, "-s", "");
		return true;
	}

	bool	setChannelReop(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isCreator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.binMode |= M_r;
		*channel << ChannelModeIsReply(gHostname, channel->name, "+r", "");
		return true;
	}

	bool	unsetChannelReop(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isCreator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.binMode &= ~M_r;
		*channel << ChannelModeIsReply(gHostname, channel->name, "-r", "");
		return true;
	}

	bool	setChannelRestrictTopic(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.binMode |= M_t;
		*channel << ChannelModeIsReply(gHostname, channel->name, "+t", "");
		return true;
	}

	bool	unsetChannelRestrictTopic(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.binMode &= ~M_t;
		*channel << ChannelModeIsReply(gHostname, channel->name, "-t", "");
		return true;
	}




	bool	setChannelLimit(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}

		channel->channelModes.l = ft::atoi(flagArguments);
		*channel << ChannelModeIsReply(gHostname, channel->name, "+l", flagArguments);
		return true;
	}

	bool	unsetChannelLimit(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.l = 0;
		*channel << ChannelModeIsReply(gHostname, channel->name, "-l", "");
		return true;
	}

	bool	addChannelKey(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.k = flagArguments;
		*channel << ChannelModeIsReply(gHostname, channel->name, "+k", flagArguments);
		return true;
	}

	bool	removeChannelKey(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)flagArguments;
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		channel->channelModes.k = "";
		*channel << ChannelModeIsReply(gHostname, channel->name, "-k", "");
		return true;
	}




	bool	addChannelBanned(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!flagArguments.size())
		{
			for (Channel::channelNicknameMap::iterator it = channel->channelModes.b.begin() ; it != channel->channelModes.b.end() ; it++)
				*user << BanListReply(gHostname, channel->name, "+", it->first);
			*user << EndOfBanListReply(gHostname, channel->name);
			return true;
		}
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		return channel->addBanned(flagArguments);
	}

	bool	removeChannelBanned(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!flagArguments.size())
		{
			for (Channel::channelNicknameMap::iterator it = channel->channelModes.b.begin() ; it != channel->channelModes.b.end() ; it++)
				*user << BanListReply(gHostname, channel->name, "+", it->first);
			*user << EndOfBanListReply(gHostname, channel->name);
			return true;
		}
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		return channel->removeBanned(flagArguments);
	}

	bool	addChannelException(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!flagArguments.size())
		{
			for (Channel::channelNicknameMap::iterator it = channel->channelModes.e.begin() ; it != channel->channelModes.e.end() ; it++)
				*user << ExceptionListReply(gHostname, channel->name, "+", it->first);
			*user << EndOfExceptionListReply(gHostname, channel->name);
			return true;
		}
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		return channel->addException(flagArguments);
	}

	bool	removeChannelException(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!flagArguments.size())
		{
			for (Channel::channelNicknameMap::iterator it = channel->channelModes.e.begin() ; it != channel->channelModes.e.end() ; it++)
				*user << ExceptionListReply(gHostname, channel->name, "+", it->first);
			*user << EndOfExceptionListReply(gHostname, channel->name);
			return true;
		}
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		return channel->removeException(flagArguments);
	}

	bool	addChannelInviteList(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!flagArguments.size())
		{
			for (Channel::channelNicknameMap::iterator it = channel->channelModes.I.begin() ; it != channel->channelModes.I.end() ; it++)
				*user << InviteListReply(gHostname, channel->name, "+", it->first);
			*user << EndOfInviteListReply(gHostname, channel->name);
			return true;
		}
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		return channel->addInviteList(flagArguments);
	}

	bool	removeChannelInviteList(Client *user, Channel *channel, std::string & flagArguments)
	{
		if (!flagArguments.size())
		{
			for (Channel::channelNicknameMap::iterator it = channel->channelModes.I.begin() ; it != channel->channelModes.I.end() ; it++)
				*user << InviteListReply(gHostname, channel->name, "+", it->first);
			*user << EndOfInviteListReply(gHostname, channel->name);
			return true;
		}
		if (!channel->isOperator(user))
		{
			*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
			return false;
		}
		return channel->removeInviteList(flagArguments);
	}


// --- parseChannelMode ---//
	bool	Server::parseChannelMode(Client *user, std::string const & channelName,
			std::string & flags, std::string & flagArguments)
	{
		Channel *channel = user->getChannelGlobal(channelName);
		if (!channel)
		{
			*user << NoSuchChannelError(gHostname, channelName);
			return false;
		}

		if (channel->isNetworkUnmoderatedChannel())
		{
			*user << NoChanModesError(gHostname, channelName);
			return false;
		}

		char sign = flags[0];
		if (sign != '+' && sign != '-')
		{
			*user << UModeUnkownFlagError(gHostname);
			return false;
		}

		flags.erase(0, 1);
		for (std::string::iterator it = flags.begin(); it != flags.end(); it++)
		{
			if (database.modeChannelFunctionsMap[sign].find(*it) == database.modeChannelFunctionsMap[sign].end())
				return false;
			database.modeChannelFunctionsMap[sign][*it](user, channel, flagArguments);
		}
		return true;
	}


// ==========   USER MODES   ========== //

	bool	setUserInvisible(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)channel;
		(void)flagArguments;
		user->clientModes.binMode |= Mu_i;
		*user << UModeIsReply(gHostname, "+i");
		return true;
	}

	bool	unsetUserInvisible(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)channel;
		(void)flagArguments;
		user->clientModes.binMode &= ~Mu_i;
		*user << UModeIsReply(gHostname, "-i");
		return true;
	}

	bool	setUserServerNotice(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)channel;
		(void)flagArguments;
		user->clientModes.binMode |= Mu_s;
		*user << UModeIsReply(gHostname, "+s");
		return true;
	}

	bool	unsetUserServerNotice(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)channel;
		(void)flagArguments;
		user->clientModes.binMode &= ~Mu_s;
		*user << UModeIsReply(gHostname, "-s");
		return true;
	}

	bool	setUserWallops(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)channel;
		(void)flagArguments;
		user->clientModes.binMode |= Mu_w;
		*user << UModeIsReply(gHostname, "+w");
		return true;
	}

	bool	unsetUserWallops(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)channel;
		(void)flagArguments;
		user->clientModes.binMode &= ~Mu_w;
		*user << UModeIsReply(gHostname, "-w");
		return true;
	}

		bool	setUserOperator(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)user;
		(void)channel;
		(void)flagArguments;
		*user << UModeIsReply(gHostname, "+o");
		return true;
	}

	bool	unsetUserOperator(Client *user, Channel *channel, std::string & flagArguments)
	{
		(void)channel;
		(void)flagArguments;
		user->clientModes.binMode &= ~Mu_o;
		*user << UModeIsReply(gHostname, "-o");
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
			*user << UModeUnkownFlagError(gHostname);
			return false;
		}

		flags.erase(0, 1);
		for (std::string::iterator it = flags.begin(); it != flags.end(); it++)
		{
			if (database.modeUserFunctionsMap[sign].find(*it) == database.modeUserFunctionsMap[sign].end())
				*user << UModeUnkownFlagError(gHostname);
			else
			{
				database.modeUserFunctionsMap[sign][*it](user, NULL, flagArguments);
				userMode.replace(1, 1, 1, *it);
				*user << UModeIsReply(gHostname, userMode);
			}
		}
		return true;
	}

}
