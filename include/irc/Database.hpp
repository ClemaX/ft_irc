#pragma once

#include <map>
#include <irc/ircdef.hpp>
#include <utils/nickname.hpp>
#include <utils/strings.hpp>
#include <irc/ModeFunctions.hpp>
#include <stdint.h>

#include <irc/AClient.hpp>
#include <irc/AServerConnection.hpp>
#include <irc/Channel.hpp>

#include <irc/ServerConfig.hpp>

namespace NAMESPACE_IRC
{
	/**
	 * 	@brief Database used to map servers,
	 * 	clients and chanels
	*/
	struct	Database
	{
		/* Member types */

		// TODO: Use custom comparators for Server and Channel maps
		typedef ::std::map<std::string, AServerConnection*>	serverMap;
		typedef ::std::map<std::string, Channel*>			channelMap;
		typedef ::std::map<std::string, AClient*, nickcmp>	clientMap;

		typedef bool (*ptr_function)(AClient *const user, Channel *const channel, const std::string & flagArguments);
		typedef std::map<char, ptr_function>				signedFunctionPointerMap;
		typedef std::map<char, signedFunctionPointerMap>	functionPointerMap;

		/* Members */ // TODO: Init in constructor
		std::string	hostname;
		std::string	motd;
		std::string	createdAt;
		std::string password;

		serverMap	dataServersMap;
		channelMap	dataChannelsMap;
		clientMap	dataClientsMap;
		functionPointerMap	modeChannelFunctionsMap;
		functionPointerMap	modeUserFunctionsMap;

		/* Member functions */

		Database();
		Database(const ServerConfig& config);
		Database(const Database& other);
		virtual ~Database() throw();

		Database& operator=(const Database& other);

		/* Database seters */

		void		addServer(AServerConnection* const server);
		void		addChannel(Channel* const channel);
		void		addClient(AClient* const client);
		void		set_ClientNick(const std::string& previous, const std::string& current);

		/* Database getters */

		AClient*	getClient(std::string const& nickname) const;
		Channel*	getChannel(std::string const& channelName) const;
		Channel*	getJoinedChannel(AClient const*const user, std::string const& channelName) const;
		Channel*	getVisibleChannel(AClient const*const user, std::string const& channelName) const;

		/* Mode pointer functions */

		void						createModeFunctionsMap();
		signedFunctionPointerMap	getPlusChannelMap();
		signedFunctionPointerMap	getMinusChannelMap();
		signedFunctionPointerMap	getPlusUserMap();
		signedFunctionPointerMap	getMinusUserMap();

		/* Parser functions */
		bool	parseUserMode(AClient *user, std::string & flags,
			std::string & flagArguments);

		bool	parseChannelMode(AClient *user, std::string const & channelName,
				std::string & flags, std::string & flagArguments);

		/* Share/Receive content between servers */
		// FIXME
		//void	init_new_server_conextion(Server* const target);
	};

	/////////////////////////////////////////////////
	// Inline IRCDatabase basic members definition //
	/////////////////////////////////////////////////

	inline
	Database::
	Database()
	{ }

	inline
	Database::
	Database(ServerConfig const& config)
		:	hostname(config[IRC_CONF_HOSTNAME]),
			motd(config[IRC_CONF_MOTD]),
			createdAt(config[IRC_CONF_CREATEDAT])
	{
		createModeFunctionsMap();
	}

	inline
	Database::
	Database(const Database& other)
	{ *this = other; }

	inline
	Database::
	~Database() throw()
	{ }	// erase all three maps ?

	///////////////////////////////////////////////////
	// Inline IRCDatabase setters members definition //
	///////////////////////////////////////////////////

	inline void
	Database::
	addServer(AServerConnection* const server)
	{ dataServersMap[server->name] = server; }

	inline void
	Database::
	addChannel(Channel* const channel)
	{ dataChannelsMap[channel->name] = channel; }

	inline void
	Database::
	addClient(AClient* const client)
	{ dataClientsMap[client->nickname] = client; }

	inline void
	Database::
	set_ClientNick(const std::string& previous, const std::string& current)
	{ const_cast<std::string&>(dataClientsMap.find(previous)->first) = current; }

	///////////////////////////////////////////////////
	// Inline IRCDatabase getters members definition //
	///////////////////////////////////////////////////

	namespace
	{
		template <typename Map>
		inline typename Map::mapped_type
		get_from_map(const Map& m, const typename Map::key_type& k)
		{
			const typename Map::const_iterator& it = m.find(k);
			return (it == m.end() ? NULL : it->second);
		}
	}

	inline AClient*
	Database::
	getClient(const std::string& nickname) const
	{ return (get_from_map(dataClientsMap, nickname)); }

	// TODO: Use insensitive compare instead of tolower

	inline Channel*
	Database::
	getChannel(const std::string& channelName) const
	{ return (get_from_map(dataChannelsMap, ft::strToLower(channelName))); }

	inline Channel*
	Database::
	getJoinedChannel(const AClient* const user, const std::string& channelName) const
	{
		Channel *channel = getChannel(channelName);

		if (!channel->isInChannel(user->nickname))
			channel = NULL;
		return channel;
	}

	/**
	 * 	@brief Return a pointer to the channel which name is channelName.
	 *
	 * 	@param channelName The name of the channel.
	 *
	 * 	NOTE: The search is done among all the channels in the database
	*/
	inline Channel*
	Database::
	getVisibleChannel(const AClient* const user, const std::string& channelName) const
	{
		Channel *channel = getJoinedChannel(user, channelName);

		if (!channel)
		{
			channel = getChannel(channelName);

			if (channel && !channel->isLocalChannelVisibleForClient(user))
				channel = NULL;
		}
		return channel;
	}

	////////////////////////////
	// Mode function pointers //
	////////////////////////////

	namespace
	{
		template <typename Map, typename func_array, typename index_array>
		Map
		for_each_assign_by_index(const func_array& f, const index_array& i, size_t amount)
		{
			Map m;
			for (size_t it = 0 ; it < amount ; it++)
				m[i[it]] = f[it];
			return (m);
		}
	}

	inline Database::signedFunctionPointerMap
	Database::
	getPlusChannelMap()
	{
		static const unsigned char indexes[] = {
			'O', 'o', 'v', 'a', 'i', 'm', 'n', 'q', 'p', 's',
			'r', 't', 'l', 'k', 'b', 'e', 'I'
		};

		static const ptr_function f[] = {
			&addChannelCreator,
			&addChannelOperator,
			&addChannelVoice,
			&setChannelAnonymous,
			&setChannelInviteOnly,
			&setChannelModerated,
			&setChannelNoExternalMessage,
			&setChannelQuiet,
			&setChannelPrivate,
			&setChannelSecret,
			&setChannelReop,
			&setChannelRestrictTopic,
			&setChannelLimit,
			&addChannelKey,
			&addChannelBanned,
			&addChannelException,
			&addChannelInviteList
		};

		return (for_each_assign_by_index<signedFunctionPointerMap>(f, indexes, ARRAY_SIZE(f)));
	}

	inline Database::signedFunctionPointerMap
	Database::
	getMinusChannelMap()
	{
		static const unsigned char indexes[] = {
			'o', 'v', 'a', 'i', 'm', 'n', 'q', 'p', 's',
			'r', 't', 'l', 'k', 'b', 'e', 'I'
		};

		static const ptr_function f[] = {
			&removeChannelOperator,
			&removeChannelVoice,
			&unsetChannelAnonymous,
			&unsetChannelInviteOnly,
			&unsetChannelModerated,
			&unsetChannelNoExternalMessage,
			&unsetChannelQuiet,
			&unsetChannelPrivate,
			&unsetChannelSecret,
			&unsetChannelReop,
			&unsetChannelRestrictTopic,
			&unsetChannelLimit,
			&removeChannelKey,
			&removeChannelBanned,
			&removeChannelException,
			&removeChannelInviteList,

		};

		return (for_each_assign_by_index<signedFunctionPointerMap>(f, indexes, ARRAY_SIZE(f)));
	}

	inline Database::signedFunctionPointerMap
	Database::
	getPlusUserMap()
	{
		static const unsigned char indexes[] = {
			'i', 's', 'w', 'o'
		};

		static const ptr_function f[] = {
			&setUserInvisible,
			&setUserServerNotice,
			&setUserWallops,
			&setUserOperator	// can a server use this function to set an operator ?
		};

		return (for_each_assign_by_index<signedFunctionPointerMap>(f, indexes, ARRAY_SIZE(f)));
	}

	inline Database::signedFunctionPointerMap
	Database::
	getMinusUserMap()
	{
		static const unsigned char indexes[] = {
			'i', 's', 'w', 'o'
		};

		static const ptr_function f[] = {
			&unsetUserInvisible,
			&unsetUserServerNotice,
			&unsetUserWallops,
			&unsetUserOperator
		};

		return (for_each_assign_by_index<signedFunctionPointerMap>(f, indexes, ARRAY_SIZE(f)));
	}

	///////////////////////////////
	// Init new server connexion //
	///////////////////////////////

	namespace
	{
		template <typename Exec, class Map, class __Target>
		void
		for_each_in_map(const Map& m, __Target* const target)
		{
			for (typename Map::const_iterator it = m.begin() ; it != m.end() ; it++)
				Exec(*it, target);
		}

		inline void
		handle_server(const AServerConnection& src, AServerConnection* const target)
		{
			// TODO: RESEARCH ABOUT THE SERVER COMMAND
			// TODO: Handle self sever name

			*target << (std::string("SERVER ") + src.name + IRC_MESSAGE_SUFFIX);
		}

		inline void
		handle_client_channels(Channel const& src, AServerConnection* const target)
		{ *target << (std::string("JOIN ") + src.name + IRC_MESSAGE_SUFFIX); }

		template <typename AddMode, size_t amount, class __Server, class __Channel>
		void
		handle_mode(const uint32_t* const flags, const char*const symbols,
		const __Channel& src, __Server* const target)
		{
			for (size_t i = 0 ; i < amount ; i++)
				if (src.binMode & flags[i])
					*target << AddMode(src, symbols[i]);
		}

		template <class __Channel>
		inline const std::string
		add_client_mode(const __Channel& src, const char*const symbol)
		{
			static_cast<void>(src);
			return (std::string("MODE ") + "+" + symbol + IRC_MESSAGE_SUFFIX);
		}

		template <class __Channel>
		inline const std::string
		add_channel_mode(const __Channel& src, const char*const symbol)
		{ return (std::string("MODE ") + src.name + " +" + symbol + IRC_MESSAGE_SUFFIX); }

		template <class __Server, class __Channel>
		inline void
		handle_client_modes(const __Channel& src, __Server* const target)
		{
			static const uint32_t		flags[] = { 1, 2, 4, 8 };
			static const char* const	symbols[] = { "i", "s", "w", "o" };

			// Parameters: <nickname> {[+|-]|i|w|s|o}

			// TO DO: Where must i add nickname ?

			handle_mode<add_client_mode, ARRAY_SIZE(flags)>(flags, symbols,src, target);
		}
/* 		void
		handle_client(const AClient& src, AServerConnection* const target)
		{
			// TO DO: Add old_nickname member ?
			// TO DO: PASS ?

			*target << (std::string("NICK ") + src.nickname + IRC_MESSAGE_SUFFIX
		//	+ std::string("PASS ") + src.password + IRC_MESSAGE_SUFFIX
			+ std::string("USER") + src.username + " " + src.hostname + " "
					+ src.servername + " " + src.realname + IRC_MESSAGE_SUFFIX);
			handle_client_modes(src, target);
			for_each_in_map<handle_client_channels>(src.channels, target);
		}

		template <class __Server, class __Channel>
		inline void
		handle_channel_modes(const __Channel& src, __Server* const target)
		{
			static const uint32_t		flags[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256 };
			static const char* const 	symbols[] = { "a", "i", "m", "n", "q", "p", "s", "r", "t" };

			handle_mode<add_channel_mode, ARRAY_SIZE(flags)>(flags, symbols, src, target);
		}

		void
		handle_channel(const Channel& src, AServerConnection* const target)
		{
			static const uint32_t		flags[] = { 1024, 2048, 4096, 8192, 16384 }; //  512 -> O
			static const char* const	symbols[] = { "o", "v", "b", "e", "I" };

			// Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]

			typedef std::map<std::string, uint32_t>::const_iterator const_iterator;

			// Channel modes
			handle_channel_modes(src, target);

			// User in channel modes
			for (const_iterator it = src.channelModes.channelModes.begin()
			; it != src.channelModes.channelModes.end() ; it++)
			{
				// TO DO: Check if i need to remove 'O' for each iteration too
				*target << (std::string("MODE ") + src.name + " -o " + it->first + IRC_MESSAGE_SUFFIX);
				for (size_t index = 0 ; index < ARRAY_SIZE(flags) ; index++)
					if (it->second & flags[index])
						*target << (std::string("MODE ") + src.name + " +"
						+ symbols[index] + it->first + IRC_MESSAGE_SUFFIX);
			}
		}

		template <class Map, class __Server>
		inline void
		send_server_data(const Map& m, __Server* const target)
		{ for_each_in_map<handle_server>(m, target); }

		template <class Map, class __Server>
		inline void
		send_client_data(const Map& m, __Server* const target)
		{ for_each_in_map<handle_client>(m, target); }

		template <class Map, class __Server>
		inline void
		send_channel_data(const Map& m, __Server* const target)
		{ for_each_in_map<handle_channel>(m, target); }
	*/

	}

/* 	// TO DO: Need to add prefixes to simulte different clients
	void
	Database::
	init_new_server_conextion(Server* const target)
	{
		// Decompose the database into commands
		// & send those commands to the target server
		send_server_data(dataServersMap, target);
		send_client_data(dataClientsMap, target);
		send_channel_data(dataChannelsMap, target);
	} */

}
