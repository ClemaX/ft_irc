#include <irc/Server.hpp>

namespace irc
{
	// TO DO: Mistake 3 are Creator not operator ...

	namespace
	{
		// 10 chars per line starting at idex 1
		static const char* const __modes[] = {
			0,
			"a", "i", 0, "m", 0, 0, 0, "n", 0, 0,
			0, 0, 0, 0, 0, "q", 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, "p", 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, "s", 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, "r", 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, "t"
		};

		template <class __Reply, class __Client, class __Channel>
		inline bool
		check_privileges(__Client* const user, __Channel *const channel)
		{
			if (!channel->isOperator(user))
			{
				*user << __Reply(gHostname, channel->name);
				return (false);
			}
			return (true);
		}

		template <class __Reply, class __Client, class __Channel>
		inline bool
		check_creator(__Client* const user, __Channel *const channel)
		{
			if (!channel->isCreator(user))
			{
				*user << __Reply(gHostname, channel->name);
				return (false);
			}
			return (true);
		}

		template <class __Reply, class __Channel>
		inline bool
		__attribute__ ((const)) // Always return the same, compiler preloads rax
		add_mode(__Channel *const channel, size_t mask)
		{
			channel->channelModes.binMode |= mask;
			*channel << __Reply(gHostname, channel->name, std::string("+") + __modes[mask], "");
			return (true);
		}

		template <class __Reply, class __Channel>
		inline bool
		__attribute__ ((const)) // Always return the same, compiler preloads rax
		reset_mode(__Channel *const channel, size_t mask)
		{
			channel->channelModes.binMode &= ~mask;
			*channel << __Reply(gHostname, channel->name, std::string("-") + __modes[mask], "");
			return (true);
		}

		template <class __Client, class __Channel>
		inline bool
		handle_mode(__Client* const user, __Channel* const channel, size_t mask)
		{
			return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
			&& add_mode<ChannelModeIsReply>(channel, mask));
		}

		template <class __Client, class __Channel>
		inline bool
		handle_mode(__Client* const user, __Channel* const channel, size_t mask, int)
		{
			return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
			&& reset_mode<ChannelModeIsReply>(channel, mask));
		}
	}

// ==========   CHANNEL MODES   ========== //

	bool
	addChannelCreator(Client *user, Channel *channel, std::string & flagArguments)
	{
		return (check_creator<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->addCreator(flagArguments));
	}

	bool
	addChannelOperator(Client *user, Channel *channel, std::string & flagArguments)
	{
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->addOperator(flagArguments));
	}

	bool
	removeChannelOperator(Client *user, Channel *channel, std::string & flagArguments)
	{
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->removeOperator(flagArguments));
	}

	bool	addChannelVoice(Client *user, Channel *channel, std::string & flagArguments)
	{
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->addVoice(flagArguments));
	}

	bool
	removeChannelVoice(Client *user, Channel *channel, std::string & flagArguments)
	{
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->addVoice(flagArguments));
	}

	// -----------------------------------------





	bool
	setChannelAnonymous(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, M_a));
	}

	bool
	unsetChannelAnonymous(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, M_a, 0));
	}


	bool
	setChannelInviteOnly(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, M_i));
	}

	bool
	unsetChannelInviteOnly(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, M_i, 0));
	}

	bool
	setChannelModerated(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, M_m));
	}

	bool
	unsetChannelModerated(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, M_m, 0));
	}

	bool
	setChannelNoExternalMessage(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, M_n));
	}

	bool
	unsetChannelNoExternalMessage(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, M_n, 0));
	}

	bool
	setChannelQuiet(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, M_q));
	}

	bool
	unsetChannelQuiet(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, M_q, 0));
	}

	bool
	setChannelPrivate(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, M_p));
	}

	bool
	unsetChannelPrivate(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, M_p, 0));
	}

	bool
	setChannelSecret(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, M_s));
	}

	bool
	unsetChannelSecret(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, M_s, 0));
	}

	bool
	setChannelReop(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(flagArguments);
		return (check_creator<ChannelOperatorPrivilegiesError>(user, channel)
		&& add_mode<ChannelModeIsReply>(channel, M_r));
	}

	bool
	unsetChannelReop(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(flagArguments);
		return (check_creator<ChannelOperatorPrivilegiesError>(user, channel)
		&& reset_mode<ChannelModeIsReply>(channel, M_r));
	}

	bool
	setChannelRestrictTopic(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, M_t));
	}

	bool
	unsetChannelRestrictTopic(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, M_t, 0));
	}

	// ----------- l & k different pattern

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


	// TO DO: b, e, I are needed in this format ?

	namespace
	{
		template <class __Ban, class __EndBan, class __Client, class __Channel, class Map>
		bool
		handle_no_args(__Client* const user, __Channel* const channel,
		const std::string& flagArguments, const Map& m)
		{
			if (flagArguments.empty() == false)
				return (false);

			for (typename Map::const_iterator it = m.begin() ; it != m.end() ; it++)
				*user << __Ban(gHostname, channel->name, "+", it->first);
			*user << __EndBan(gHostname, channel->name);
			return (true);
		}
	}

	bool
	addChannelBanned(Client *user, Channel *channel, std::string & flagArguments)
	{
		if  (handle_no_args<BanListReply,EndOfBanListReply>(user, channel,
		flagArguments, channel->channelModes.b))
			return (true);
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->addBanned(flagArguments));
	}

	bool
	removeChannelBanned(Client *user, Channel *channel, std::string & flagArguments)
	{
		if  (handle_no_args<BanListReply,EndOfBanListReply>(user, channel,
		flagArguments, channel->channelModes.b))
			return (true);
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->removeBanned(flagArguments));
	}

	bool
	addChannelException(Client *user, Channel *channel, std::string & flagArguments)
	{
		if  (handle_no_args<ExceptionListReply,EndOfExceptionListReply>(user, channel,
		flagArguments, channel->channelModes.e))
			return (true);
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->addException(flagArguments));
	}

	bool
	removeChannelException(Client *user, Channel *channel, std::string & flagArguments)
	{
		if  (handle_no_args<ExceptionListReply,EndOfExceptionListReply>(user, channel,
		flagArguments, channel->channelModes.e))
			return (true);
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->removeException(flagArguments));
	}

	bool
	addChannelInviteList(Client *user, Channel *channel, std::string & flagArguments)
	{
		if  (handle_no_args<InviteListReply,EndOfInviteListReply>(user, channel,
		flagArguments, channel->channelModes.I))
			return (true);
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->addInviteList(flagArguments));
	}

	bool
	removeChannelInviteList(Client *user, Channel *channel, std::string & flagArguments)
	{
		if  (handle_no_args<InviteListReply,EndOfInviteListReply>(user, channel,
		flagArguments, channel->channelModes.I))
			return (true);
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->removeInviteList(flagArguments));
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

	bool
	__attribute__ ((const))
	setUserInvisible(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->clientModes.binMode |= Mu_i;
		*user << UModeIsReply(gHostname, "+i");
		return (true);
	}

	bool
	__attribute__ ((const))
	unsetUserInvisible(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->clientModes.binMode &= ~Mu_i;
		*user << UModeIsReply(gHostname, "-i");
		return (true);
	}

	bool
	__attribute__ ((const))
	setUserServerNotice(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->clientModes.binMode |= Mu_s;
		*user << UModeIsReply(gHostname, "+s");
		return (true);
	}

	bool
	__attribute__ ((const))
	unsetUserServerNotice(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->clientModes.binMode &= ~Mu_s;
		*user << UModeIsReply(gHostname, "-s");
		return (true);
	}

	bool
	__attribute__ ((const))
	setUserWallops(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->clientModes.binMode |= Mu_w;
		*user << UModeIsReply(gHostname, "+w");
		return (true);
	}

	bool
	__attribute__ ((const))
	unsetUserWallops(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->clientModes.binMode &= ~Mu_w;
		*user << UModeIsReply(gHostname, "-w");
		return (true);
	}

	bool
	__attribute__ ((const))
	setUserOperator(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		*user << UModeIsReply(gHostname, "+o");
		return (true);
	}

	bool
	__attribute__ ((const))
	unsetUserOperator(Client *user, Channel *channel, std::string & flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->clientModes.binMode &= ~Mu_o;
		*user << UModeIsReply(gHostname, "-o");
		return (true);
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
