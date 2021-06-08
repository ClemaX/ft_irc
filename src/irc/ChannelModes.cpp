#include <irc/Server.hpp>
#include <irc/Channel.hpp>

#include <irc/AClient.hpp>
#include <irc/PrivateMessage.hpp>

namespace NAMESPACE_IRC
{
	typedef Channel<Server, AClient> __Channel;

	namespace
	{
		// 10 chars* per line starting at {1, 1}
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

		template <class __Client, class __Channel>
		inline bool
		__attribute__ ((const)) // Always return the same, compiler preloads rax
		add_mode(__Client* const user, __Channel *const channel, size_t mask)
		{
			channel->channelModes |= mask;
			// *channel << __Reply(gHostname, channel->name, std::string("+") + __modes[mask], "");
			*channel << ModeChannelMessage(user->nickname, channel->name, '+', __modes[mask]);
			return (true);
		}

		template <class __Client, class __Channel>
		inline bool
		__attribute__ ((const)) // Always return the same, compiler preloads rax
		reset_mode(__Client* const user, __Channel *const channel, size_t mask)
		{
			channel->channelModes &= ~mask;
			// *channel << __Reply(gHostname, channel->name, std::string("-") + __modes[mask], "");
			*channel << ModeChannelMessage(user->nickname, channel->name, '-', __modes[mask]);
			return (true);
		}

		template <class __Client, class __Channel>
		inline bool
		handle_mode(__Client* const user, __Channel* const channel, size_t mask)
		{
			return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
			&& add_mode<__Client, __Channel>(user, channel, mask));
		}

		template <class __Client, class __Channel>
		inline bool
		handle_mode(__Client* const user, __Channel* const channel, size_t mask, int)
		{
			return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
			&& reset_mode<__Client, __Channel>(user, channel, mask));
		}
	}

	bool
	addChannelCreator(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		return (check_creator<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->addCreator(flagArguments));
	}

	bool
	addChannelOperator(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->addOperator(flagArguments));
	}

	bool
	removeChannelOperator(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->removeOperator(flagArguments));
	}

	bool	addChannelVoice(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->addVoice(flagArguments));
	}

	bool
	removeChannelVoice(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->addVoice(flagArguments));
	}

	bool
	setChannelAnonymous(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, __Channel::a));
	}

	bool
	unsetChannelAnonymous(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, __Channel::a, 0));
	}


	bool
	setChannelInviteOnly(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, __Channel::i));
	}

	bool
	unsetChannelInviteOnly(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, __Channel::i, 0));
	}

	bool
	setChannelModerated(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, __Channel::m));
	}

	bool
	unsetChannelModerated(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, __Channel::m, 0));
	}

	bool
	setChannelNoExternalMessage(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, __Channel::n));
	}

	bool
	unsetChannelNoExternalMessage(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, __Channel::n, 0));
	}

	bool
	setChannelQuiet(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, __Channel::q));
	}

	bool
	unsetChannelQuiet(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, __Channel::q, 0));
	}

	bool
	setChannelPrivate(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, __Channel::p));
	}

	bool
	unsetChannelPrivate(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, __Channel::p, 0));
	}

	bool
	setChannelSecret(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, __Channel::s));
	}

	bool
	unsetChannelSecret(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, __Channel::s, 0));
	}

	bool
	setChannelReop(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		// return (check_creator<ChannelOperatorPrivilegiesError>(user, channel)
		// && add_mode<ChannelModeIsReply>(channel, __Channel::r));
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& add_mode<AClient, __Channel>(user, channel, __Channel::r));
	}

	bool
	unsetChannelReop(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		// return (check_creator<ChannelOperatorPrivilegiesError>(user, channel)
		// && reset_mode<ChannelModeIsReply>(channel, __Channel::r));
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& reset_mode<AClient, __Channel>(user, channel, __Channel::r));
	}

	bool
	setChannelRestrictTopic(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, __Channel::t));
	}

	bool
	unsetChannelRestrictTopic(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, __Channel::t, 0));
	}

	bool
	setChannelLimit(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		if (!check_privileges<ChannelOperatorPrivilegiesError>(user, channel))
			return (false);

		channel->channelModes.l = ft::atoi(flagArguments);
		*channel << ChannelModeIsReply(gHostname, channel->name, "+l", flagArguments);
		return (true);
	}

	bool
	unsetChannelLimit(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		if (!check_privileges<ChannelOperatorPrivilegiesError>(user, channel))
			return (false);
		channel->channelModes.l = 0;
		*channel << ChannelModeIsReply(gHostname, channel->name, "-l", "");
		return (true);
	}

	bool
	addChannelKey(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		if (!check_privileges<ChannelOperatorPrivilegiesError>(user, channel))
			return (false);
		channel->channelModes.k = flagArguments;
		*channel << ChannelModeIsReply(gHostname, channel->name, "+k", flagArguments);
		return (true);
	}

	bool
	removeChannelKey(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		if (!check_privileges<ChannelOperatorPrivilegiesError>(user, channel))
			return (false);
		channel->channelModes.k.clear();
		*channel << ChannelModeIsReply(gHostname, channel->name, "-k", "");
		return (true);
	}

	namespace
	{
		template <class __Reply, class __EndReply, class __Client, class __Channel, class Map>
		bool
		handle_no_args(__Client* const user, __Channel* const channel,
		const std::string& flagArguments, const Map& m, size_t mask)
		{
			if (flagArguments.empty() == false)
				return (false);

			for (typename Map::const_iterator it = m.begin() ; it != m.end() ; it++)
				if (it->second & mask)
					*user << __Reply(gHostname, channel->name, "+", it->first);
			*user << __EndReply(gHostname, channel->name);
			return (true);
		}
	}

	bool
	addChannelBanned(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		if (handle_no_args<BanListReply,EndOfBanListReply>(user, channel,
		flagArguments, channel->channelModes.channelModes, __Channel::b))
			return (true);
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->addBanned(flagArguments));
	}

	bool
	removeChannelBanned(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		if  (handle_no_args<BanListReply,EndOfBanListReply>(user, channel,
		flagArguments, channel->channelModes.channelModes, __Channel::b))
			return (true);
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->removeBanned(flagArguments));
	}

	bool
	addChannelException(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		if  (handle_no_args<ExceptionListReply,EndOfExceptionListReply>(user, channel,
		flagArguments, channel->channelModes.channelModes, __Channel::e))
			return (true);
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->addException(flagArguments));
	}

	bool
	removeChannelException(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		if  (handle_no_args<ExceptionListReply,EndOfExceptionListReply>(user, channel,
		flagArguments, channel->channelModes.channelModes, __Channel::e))
			return (true);
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->removeException(flagArguments));
	}

	bool
	addChannelInviteList(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		if  (handle_no_args<InviteListReply,EndOfInviteListReply>(user, channel,
		flagArguments, channel->channelModes.channelModes, __Channel::I))
			return (true);
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->addInviteList(flagArguments));
	}

	bool
	removeChannelInviteList(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		if  (handle_no_args<InviteListReply,EndOfInviteListReply>(user, channel,
		flagArguments, channel->channelModes.channelModes, __Channel::I))
			return (true);
		return (check_privileges<ChannelOperatorPrivilegiesError>(user, channel)
		&& channel->removeInviteList(flagArguments));
	}

	////////////////////////
	// Parse channel mode //
	////////////////////////

	bool	Server::parseChannelMode(AClient *user, std::string const & channelName,
			std::string & flags, std::string & flagArguments)
	{
		__Channel *channel = user->getChannelGlobal(database, channelName);
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
			// *channel << ModeChannelMessage(user->nickname, channelName, sign, *it);
		}
		return true;
	}

	////////////////
	// User Modes //
	////////////////

	bool
	__attribute__ ((const))
	setUserInvisible(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->modes.set(AClient::i);
		*user << UModeIsReply(gHostname, "+i");
		return (true);
	}

	bool
	__attribute__ ((const))
	unsetUserInvisible(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->modes.unset(AClient::i);
		*user << UModeIsReply(gHostname, "-i");
		return (true);
	}

	bool
	__attribute__ ((const))
	setUserServerNotice(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->modes.set(AClient::s);
		*user << UModeIsReply(gHostname, "+s");
		return (true);
	}

	bool
	__attribute__ ((const))
	unsetUserServerNotice(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->modes.unset(AClient::s);
		*user << UModeIsReply(gHostname, "-s");
		return (true);
	}

	bool
	__attribute__ ((const))
	setUserWallops(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->modes.set(AClient::w);
		*user << UModeIsReply(gHostname, "+w");
		return (true);
	}

	bool
	__attribute__ ((const))
	unsetUserWallops(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->modes.unset(AClient::w);
		*user << UModeIsReply(gHostname, "-w");
		return (true);
	}

	bool
	__attribute__ ((const))
	setUserOperator(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->modes.set(AClient::o);
		*user << UModeIsReply(gHostname, "+o");
		return (true);
	}

	bool
	__attribute__ ((const))
	unsetUserOperator(AClient* const user, __Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->modes.unset(AClient::o);
		*user << UModeIsReply(gHostname, "-o");
		return (true);
	}

	////////////////
	// Parse Mode //
	////////////////

	bool	Server::parseUserMode(AClient *user, std::string & flags, std::string & flagArguments)
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
