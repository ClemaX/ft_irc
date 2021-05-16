#pragma once

#include <map>
#include <irc/ircdef.hpp>
#include <utils/nickname.hpp>
#include <utils/strings.hpp>
#include <irc/Modes_functions.hpp>

namespace irc
{
	/**
	 * 	@brief Database used to map servers,
	 * 	clients and chanels
	*/
	template <class Server, class Client, class Channel>
	struct	IRCDatabase
	{
		/* Member types */

		typedef typename ::std::map<Server*, Server*>				databaseServersMap;
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
		dataServersMap[server] = server;
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
}
