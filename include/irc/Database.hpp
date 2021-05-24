#pragma once

#include <map>
#include <irc/ircdef.hpp>
#include <utils/nickname.hpp>
#include <utils/strings.hpp>
#include <irc/Modes_functions.hpp>
#include <stdint.h>

namespace NAMESPACE_IRC
{
	/**
	 * 	@brief Database used to map servers,
	 * 	clients and chanels
	*/
	template <class Server, class Client, class Channel>
	struct	IRCDatabase
	{
		/* Member types */

		// TODO: Use custom comparators for Server and Channel maps
		typedef typename ::std::map<std::string, Server*>			databaseServersMap;
		typedef typename ::std::map<std::string, Channel*>			databaseChannelsMap;
		typedef typename ::std::map<std::string, Client*, nickcmp>	databaseClientsMap;

		typedef bool (*ptr_function)(Client *const user, Channel *const channel, const std::string & flagArguments);
		typedef	typename std::map<char, ptr_function>				signedFunctionPointerMap;
		typedef	typename std::map<char, signedFunctionPointerMap>	functionPointerMap;

		/* Members */

		databaseServersMap	dataServersMap;
		databaseChannelsMap	dataChannelsMap;
		databaseClientsMap	dataClientsMap;
		functionPointerMap	modeChannelFunctionsMap;
		functionPointerMap	modeUserFunctionsMap;

		/* Member functions */

		IRCDatabase();
		IRCDatabase(Server* const server);
		IRCDatabase(const IRCDatabase& other);
		virtual ~IRCDatabase() throw();

		IRCDatabase& operator=(const IRCDatabase& other);

		/* Database seters */

		void		addServer(Server* const server);
		void		addChannel(Channel* const channel);
		void		addClient(Client* const client);
		void		set_ClientNick(const std::string& previous, const std::string& current);

		/* Database getters */

		Client*		getClient(std::string const &nickname) const;
		Channel*	getChannel(std::string const &channelName) const;

		/* Mode pointer functions */

		void						createModeFunctionsMap();
		signedFunctionPointerMap	getPlusChannelMap();
		signedFunctionPointerMap	getMinusChannelMap();
		signedFunctionPointerMap	getPlusUserMap();
		signedFunctionPointerMap	getMinusUserMap();

		/* Share/Receive content between servers */

		void	init_new_server_conextion(Server* const target);
	};

	/////////////////////////////////////////////////
	// Inline IRCDatabase basic members definition //
	/////////////////////////////////////////////////

	template <class Server, class Client, class Channel>
	inline
	IRCDatabase<Server, Client, Channel>::
	IRCDatabase()
	{ }

	template <class Server, class Client, class Channel>
	inline
	IRCDatabase<Server, Client, Channel>::
	IRCDatabase(Server* const server)
	{
		// TODO: Add servername
		dataServersMap[server->get_hostname()] = server;
		createModeFunctionsMap();
	}	// Do we have to add the clients and channels of server ?

	template <class Server, class Client, class Channel>
	inline
	IRCDatabase<Server, Client, Channel>::
	IRCDatabase(const IRCDatabase& other)
	{ *this = other; }

	template <class Server, class Client, class Channel>
	inline
	IRCDatabase<Server, Client, Channel>::
	~IRCDatabase() throw()
	{ }	// erase all three maps ?

	template <class Server, class Client, class Channel>
	IRCDatabase<Server, Client, Channel>&
	IRCDatabase<Server, Client, Channel>::
	operator=(const IRCDatabase& other)
	{
		if (this != &other)
		{
			dataServersMap = other.dataServersMap;
			dataChannelsMap = other.dataChannelsMap;
			dataClientsMap = other.dataClientsMap;
			modeChannelFunctionsMap = other.modeChannelFunctionsMap;
			modeUserFunctionsMap = other.modeUserFunctionsMap;
		}
		return (*this);
	}

	///////////////////////////////////////////////////
	// Inline IRCDatabase setters members definition //
	///////////////////////////////////////////////////

	namespace
	{
		/**
		 * 	@brief uses operator[] @a Map
		 *
		 * 	@tparam Map a std::map.
		 * 	@tparam Key the index in the map.
		 * 	@tparam Value what will be inserted at @a Key
		*/
		template <typename Map, typename Key ,typename Value>
		inline void
		insert_value_at_key(Map& m, const Key& k, const Value& v)
		{ m[k] = v; }
	}

	template <class Server, class Client, class Channel>
	inline void
	IRCDatabase<Server, Client, Channel>::
	addServer(Server* const server)
	{ insert_value_at_key(dataServersMap, server, server); }

	template <class Server, class Client, class Channel>
	inline void
	IRCDatabase<Server, Client, Channel>::
	addChannel(Channel* const channel)
	{ insert_value_at_key(dataChannelsMap, channel->name, channel); }

	template <class Server, class Client, class Channel>
	inline void
	IRCDatabase<Server, Client, Channel>::
	addClient(Client* const client)
	{ insert_value_at_key(dataClientsMap, client->nickname, client); }

	template <class Server, class Client, class Channel>
	inline void
	IRCDatabase<Server, Client, Channel>::
	set_ClientNick(const std::string& previous, const std::string& current)
	{ const_cast<std::string&>(dataClientsMap.find(previous)->first) = current; }

	///////////////////////////////////////////////////
	// Inline IRCDatabase getters members definition //
	///////////////////////////////////////////////////

	namespace
	{
		template <typename Value, typename Map, typename Key>
		inline Value
		get_from_map(const Map& m, const Key& k)
		{
			const typename Map::const_iterator& it = m.find(k);
			return (it == m.end() ? NULL : it->second);
		}
	}

	template <class Server, class Client, class Channel>
	inline Client*
	IRCDatabase<Server, Client, Channel>::
	getClient(const std::string& nickname) const
	{ return (get_from_map<Client*>(dataClientsMap, nickname)); }

	template <class Server, class Client, class Channel>
	inline Channel*
	IRCDatabase<Server, Client, Channel>::
	getChannel(const std::string& channelName) const
	{ return (get_from_map<Channel*>(dataChannelsMap, ft::strToLower(channelName))); }

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

	template <class Server, class Client, class Channel>
	void
	IRCDatabase<Server, Client, Channel>::
	createModeFunctionsMap()
	{
		modeChannelFunctionsMap['+'] = getPlusChannelMap();
		modeChannelFunctionsMap['-'] = getMinusChannelMap();
		modeUserFunctionsMap['+'] = getPlusUserMap();
		modeUserFunctionsMap['-'] = getMinusUserMap();
	}

	template <class Server, class Client, class Channel>
	inline typename IRCDatabase<Server, Client, Channel>::signedFunctionPointerMap
	IRCDatabase<Server, Client, Channel>::
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

	template <class Server, class Client, class Channel>
	inline typename IRCDatabase<Server, Client, Channel>::signedFunctionPointerMap
	IRCDatabase<Server, Client, Channel>::
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

	template <class Server, class Client, class Channel>
	inline typename IRCDatabase<Server, Client, Channel>::signedFunctionPointerMap
	IRCDatabase<Server, Client, Channel>::
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

	template <class Server, class Client, class Channel>
	inline typename IRCDatabase<Server, Client, Channel>::signedFunctionPointerMap
	IRCDatabase<Server, Client, Channel>::
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
		template <typename Exec, class Map, class __Server>
		void
		for_each_in_map(const Map& m, __Server* const target)
		{
			for (typename Map::const_iterator it = m.begin() ; it != m.end() ; it++)
				Exec(*it, target);
		}

		template <class __Server>
		inline void
		handle_server(const __Server& src, __Server* const target)
		{
			// TO DO: RESEARCH ABOUT THE SERVER COMMAND

			*target << (std::string("SERVER ") + src.hostname + IRC_MESSAGE_SUFFIX);
		}

		template <class __Server, class __Channel>
		inline void
		handle_client_channels(const __Channel& src, __Server* const target)
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

		template <class __Server, class __Client>
		void
		handle_client(const __Client& src, __Server* const target)
		{
			// TO DO: Add old_nickname member ?
			// TO DO: PASS ?

			*target << (std::string("NICK ") + src.nickname + IRC_MESSAGE_SUFFIX
		/*	+ std::string("PASS ") + src.password + IRC_MESSAGE_SUFFIX */
			+ std::string("USER") + src.username + " " + src.hostname + " "
					+ src.servername + " " + src.realname + IRC_MESSAGE_SUFFIX);
			handle_client_modes(src, target);
			for_each_in_map<handle_client_channels<__Server, __Client> >(src.clientChannels, target);
		}

		template <class __Server, class __Channel>
		inline void
		handle_channel_modes(const __Channel& src, __Server* const target)
		{
			static const uint32_t		flags[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256 };
			static const char* const 	symbols[] = { "a", "i", "m", "n", "q", "p", "s", "r", "t" };

			handle_mode<add_channel_mode, ARRAY_SIZE(flags)>(flags, symbols, src, target);
		}

		template <class __Server, class __Channel>
		void
		handle_channel(const __Channel& src, __Server* const target)
		{
			static const uint32_t		flags[] = { /* 512,*/ 1024, 2048, 4096, 8192, 16384 };
			static const char* const	symbols[] = { /*"O",*/ "o", "v", "b", "e", "I" };

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
		{ for_each_in_map<handle_server<Server> >(m, target); }

		template <class Map, class __Server>
		inline void
		send_client_data(const Map& m, __Server* const target)
		{ for_each_in_map<handle_client<Server, AClient> >(m, target); }

		template <class Map, class __Server>
		inline void
		send_channel_data(const Map& m, __Server* const target)
		{ for_each_in_map<handle_channel<Server, Channel> >(m, target); }

	}

	// TO DO: Need to add prefixes to simulte different clients
	template <class Server, class Client, class Channel>
	void
	IRCDatabase<Server, Client, Channel>::
	init_new_server_conextion(Server* const target)
	{
		// Decompose the database into commands
		// & send those commands to the target server
		send_server_data(dataServersMap, target);
		send_client_data(dataClientsMap, target);
		send_channel_data(dataChannelsMap, target);
	}

}
