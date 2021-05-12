#pragma once

#include <map>
#include <irc/ircdef.hpp>
#include <utils/nickname.hpp>
#include <utils/strings.hpp>

namespace irc
{
	class Server;
	class Client;
	class Channel;

	/**
	 * 	@brief Database used to map servers,
	 * 	clients and chanels
	*/
	struct	IRCDatabase
	{
		/* Member types */

		typedef ::std::map<Server*, Server*>				databaseServersMap;
		typedef ::std::map<std::string, Channel*>			databaseChannelsMap;
		typedef ::std::map<std::string, Client*, nickcmp>	databaseClientsMap;

		typedef bool (*ptr_function)(Client *user, Channel *channel, std::string & flagArguments);
		typedef	std::map<char, ptr_function>				signedFunctionPointerMap;
		typedef	std::map<char, signedFunctionPointerMap>	functionPointerMap;

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

		void		createModeFunctionsMap();
		signedFunctionPointerMap	getPlusChannelMap();
		signedFunctionPointerMap	getMinusChannelMap();
		signedFunctionPointerMap	getPlusUserMap();
		signedFunctionPointerMap	getMinusUserMap();
	};

	/////////////////////////////////////////////////
	// Inline IRCDatabase basic members definition //

	inline
	IRCDatabase::IRCDatabase()
	{ }

	inline
	IRCDatabase::IRCDatabase(Server* const server)
	{
		dataServersMap[server] = server;
		createModeFunctionsMap();
	}	// Do we have to add the clients and channels of server ?

	inline
	IRCDatabase::IRCDatabase(const IRCDatabase& other)
	{ *this = other; }


	inline
	IRCDatabase::~IRCDatabase() throw()
	{ }	// erase all three maps ?

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
		insert_at_value(Map& m, const Key& k, const Value& v)
		{ m[k] = v; }
	}

	inline void
	IRCDatabase::addServer(Server *server)
	{ insert_at_value(dataServersMap, server, server); }

	// Can't be declared cause of formard declaration ...
	/*
	inline void
	IRCDatabase::addChannel(Channel *channel)
	{ insert_at_value(dataChannelsMap, channel->name, channel); }

	// Same for addClient.
	*/

	inline void
	IRCDatabase::set_ClientNick(const std::string& previous, const std::string& current)
	{ const_cast<std::string&>(dataClientsMap.find(previous)->first) = current; }

	///////////////////////////////////////////////////
	// Inline IRCDatabase getters members definition //
	///////////////////////////////////////////////////

	inline Client*
	IRCDatabase::getClient(const std::string &nickname) const
	{
		const databaseClientsMap::const_iterator& it = dataClientsMap.find(nickname);
		return (it == dataClientsMap.end() ? NULL : it->second);
	}

	inline Channel*
	IRCDatabase::getChannel(const std::string& channelName) const
	{
		const databaseChannelsMap::const_iterator& it = dataChannelsMap.find(ft::strToLower(channelName));
		return (it == dataChannelsMap.end() ? NULL : it->second);
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

	// TO HERE INLINE MODES PTR FUNCTIONS

	////////////////
	// User modes //
	////////////////

	bool	setUserInvisible(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetUserInvisible(Client *user, Channel *channel, std::string & flagArguments);

	bool	setUserServerNotice(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetUserServerNotice(Client *user, Channel *channel, std::string & flagArguments);

	bool	setUserWallops(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetUserWallops(Client *user, Channel *channel, std::string & flagArguments);

	bool	setUserOperator(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetUserOperator(Client *user, Channel *channel, std::string & flagArguments);

}
