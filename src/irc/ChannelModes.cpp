#include <irc/Server.hpp>
#include <irc/Channel.hpp>

#include <irc/AClient.hpp>

namespace NAMESPACE_IRC
{
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

		inline bool
		check_privileges(AClient* const user, Channel *const channel)
		{
			if (!channel->isOperator(user))
			{
				*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
				return (false);
			}
			return (true);
		}

		inline bool
		check_creator(AClient* const user, Channel *const channel)
		{
			if (!channel->isCreator(user))
			{
				*user << ChannelOperatorPrivilegiesError(gHostname, channel->name);
				return (false);
			}
			return (true);
		}

		inline bool
		__attribute__ ((const)) // Always return the same, compiler preloads rax
		add_mode(Channel *const channel, size_t mask)
		{
			channel->channelModes |= mask;
			*channel << ChannelModeIsReply(gHostname, channel->name, std::string("+") + __modes[mask], "");
			return (true);
		}

		inline bool
		__attribute__ ((const)) // Always return the same, compiler preloads rax
		reset_mode(Channel *const channel, size_t mask)
		{
			channel->channelModes &= ~mask;
			*channel << ChannelModeIsReply(gHostname, channel->name, std::string("-") + __modes[mask], "");
			return (true);
		}

		inline bool
		handle_mode(AClient* const user, Channel* const channel, size_t mask)
		{
			return (check_privileges(user, channel)
			&& add_mode(channel, mask));
		}

		inline bool
		handle_mode(AClient* const user, Channel* const channel, size_t mask, int)
		{
			return (check_privileges(user, channel)
			&& reset_mode(channel, mask));
		}
	}

	bool
	addChannelCreator(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		return (check_creator(user, channel)
		&& channel->addCreator(flagArguments));
	}

	bool
	addChannelOperator(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		return (check_privileges(user, channel)
		&& channel->addOperator(flagArguments));
	}

	bool
	removeChannelOperator(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		return (check_privileges(user, channel)
		&& channel->removeOperator(flagArguments));
	}

	bool	addChannelVoice(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		return (check_privileges(user, channel)
		&& channel->addVoice(flagArguments));
	}

	bool
	removeChannelVoice(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		return (check_privileges(user, channel)
		&& channel->addVoice(flagArguments));
	}

	bool
	setChannelAnonymous(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, Channel::a));
	}

	bool
	unsetChannelAnonymous(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, Channel::a, 0));
	}


	bool
	setChannelInviteOnly(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, Channel::i));
	}

	bool
	unsetChannelInviteOnly(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, Channel::i, 0));
	}

	bool
	setChannelModerated(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, Channel::m));
	}

	bool
	unsetChannelModerated(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, Channel::m, 0));
	}

	bool
	setChannelNoExternalMessage(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, Channel::n));
	}

	bool
	unsetChannelNoExternalMessage(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, Channel::n, 0));
	}

	bool
	setChannelQuiet(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, Channel::q));
	}

	bool
	unsetChannelQuiet(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, Channel::q, 0));
	}

	bool
	setChannelPrivate(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, Channel::p));
	}

	bool
	unsetChannelPrivate(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, Channel::p, 0));
	}

	bool
	setChannelSecret(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, Channel::s));
	}

	bool
	unsetChannelSecret(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, Channel::s, 0));
	}

	bool
	setChannelReop(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (check_creator(user, channel)
		&& add_mode(channel, Channel::r));
	}

	bool
	unsetChannelReop(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (check_creator(user, channel)
		&& reset_mode(channel, Channel::r));
	}

	bool
	setChannelRestrictTopic(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, Channel::t));
	}

	bool
	unsetChannelRestrictTopic(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		return (handle_mode(user, channel, Channel::t, 0));
	}

	bool
	setChannelLimit(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		if (!check_privileges(user, channel))
			return (false);

		channel->channelModes.l = ft::atoi(flagArguments);
		*channel << ChannelModeIsReply(gHostname, channel->name, "+l", flagArguments);
		return (true);
	}

	bool
	unsetChannelLimit(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		if (!check_privileges(user, channel))
			return (false);
		channel->channelModes.l = 0;
		*channel << ChannelModeIsReply(gHostname, channel->name, "-l", "");
		return (true);
	}

	bool
	addChannelKey(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		if (!check_privileges(user, channel))
			return (false);
		channel->channelModes.k = flagArguments;
		*channel << ChannelModeIsReply(gHostname, channel->name, "+k", flagArguments);
		return (true);
	}

	bool
	removeChannelKey(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(flagArguments);
		if (!check_privileges(user, channel))
			return (false);
		channel->channelModes.k.clear();
		*channel << ChannelModeIsReply(gHostname, channel->name, "-k", "");
		return (true);
	}

	namespace
	{
		template <class __Reply, class __EndReply, class AClient, class Channel, class Map>
		bool
		handle_no_args(AClient* const user, Channel* const channel,
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
	addChannelBanned(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		if (handle_no_args<BanListReply,EndOfBanListReply>(user, channel,
		flagArguments, channel->channelModes.channelModes, Channel::b))
			return (true);
		return (check_privileges(user, channel)
		&& channel->addBanned(flagArguments));
	}

	bool
	removeChannelBanned(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		if  (handle_no_args<BanListReply,EndOfBanListReply>(user, channel,
		flagArguments, channel->channelModes.channelModes, Channel::b))
			return (true);
		return (check_privileges(user, channel)
		&& channel->removeBanned(flagArguments));
	}

	bool
	addChannelException(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		if  (handle_no_args<ExceptionListReply,EndOfExceptionListReply>(user, channel,
		flagArguments, channel->channelModes.channelModes, Channel::e))
			return (true);
		return (check_privileges(user, channel)
		&& channel->addException(flagArguments));
	}

	bool
	removeChannelException(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		if  (handle_no_args<ExceptionListReply,EndOfExceptionListReply>(user, channel,
		flagArguments, channel->channelModes.channelModes, Channel::e))
			return (true);
		return (check_privileges(user, channel)
		&& channel->removeException(flagArguments));
	}

	bool
	addChannelInviteList(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		if  (handle_no_args<InviteListReply,EndOfInviteListReply>(user, channel,
		flagArguments, channel->channelModes.channelModes, Channel::I))
			return (true);
		return (check_privileges(user, channel)
		&& channel->addInviteList(flagArguments));
	}

	bool
	removeChannelInviteList(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		if  (handle_no_args<InviteListReply,EndOfInviteListReply>(user, channel,
		flagArguments, channel->channelModes.channelModes, Channel::I))
			return (true);
		return (check_privileges(user, channel)
		&& channel->removeInviteList(flagArguments));
	}


	////////////////
	// User Modes //
	////////////////

	bool
	__attribute__ ((const))
	setUserInvisible(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->modes.set(AClient::i);
		*user << UModeIsReply(gHostname, "+i");
		return (true);
	}

	bool
	__attribute__ ((const))
	unsetUserInvisible(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->modes.unset(AClient::i);
		*user << UModeIsReply(gHostname, "-i");
		return (true);
	}

	bool
	__attribute__ ((const))
	setUserServerNotice(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->modes.set(AClient::s);
		*user << UModeIsReply(gHostname, "+s");
		return (true);
	}

	bool
	__attribute__ ((const))
	unsetUserServerNotice(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->modes.unset(AClient::s);
		*user << UModeIsReply(gHostname, "-s");
		return (true);
	}

	bool
	__attribute__ ((const))
	setUserWallops(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->modes.set(AClient::w);
		*user << UModeIsReply(gHostname, "+w");
		return (true);
	}

	bool
	__attribute__ ((const))
	unsetUserWallops(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->modes.unset(AClient::w);
		*user << UModeIsReply(gHostname, "-w");
		return (true);
	}

	bool
	__attribute__ ((const))
	setUserOperator(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->modes.set(AClient::o);
		*user << UModeIsReply(gHostname, "+o");
		return (true);
	}

	bool
	__attribute__ ((const))
	unsetUserOperator(AClient* const user, Channel *const channel, const std::string& flagArguments)
	{
		static_cast<void>(channel);
		static_cast<void>(flagArguments);
		user->modes.unset(AClient::o);
		*user << UModeIsReply(gHostname, "-o");
		return (true);
	}
}
