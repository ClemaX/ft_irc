#include <irc/Database.hpp>
# include "namespaces.hpp"

namespace IRC
{
    IRCDatabase::IRCDatabase()
	: dataServersMap(), dataChannelsMap(), dataClientsMap(),
	    modeChannelFunctionsMap(), modeUserFunctionsMap()
	{ }

	IRCDatabase::IRCDatabase(Server* const server)

	: dataServersMap(), dataChannelsMap(), dataClientsMap(),
		modeChannelFunctionsMap(), modeUserFunctionsMap()
	{
		dataServersMap[server] = server;
		createModeFunctionsMap();
	}	// Do we have to add the clients and channels of server ?

	IRCDatabase::~IRCDatabase()
	{ }	// erase all three maps ?

// --- Add functions --- //

	inline void
    IRCDatabase::addServer(Server* const server)
	{ dataServersMap[server] = server; }

	inline void
    IRCDatabase::addChannel(Channel* const channel)
	{ dataChannelsMap[channel->name] = channel; }

	inline void
    IRCDatabase::addClient(Client* const client)
	{ dataClientsMap[client->nickname] = client; }		// use of nickname ?


// --- Display functions --- //

	inline void
    IRCDatabase::displayAllChannelsInfo(void) const
	{
		for (databaseChannelsMap::const_iterator it = dataChannelsMap.begin() ; it != dataChannelsMap.end() ; it++)
			it->second->displayInfo();
	}


// --- Channel Mode pointer functions --- //

	inline void
    IRCDatabase::createModeFunctionsMap()
	{
        // I m not sure if that will work fine 

        static const char symbols[] = { '+', '-' };
        static const functionPointerMap targets[] = { modeChannelFunctionsMap, modeUserFunctionsMap };
        static signedFunctionPointerMap (*const maps[])() = {
            &getPlusChannelMap,
            &getMinusChannelMap,
            &getPlusUserMap,
            &getMinusUserMap
        };
        
        for (size_t i = 0 ; i < sizeof(maps) / sizeof(*maps) ; i++)
            targets[i % 2][symbols[i % 2]] = maps[i];

    /* // OLD
		modeChannelFunctionsMap['+'] = getPlusChannelMap();
		modeChannelFunctionsMap['-'] = getMinusChannelMap();
		modeUserFunctionsMap['+'] = getPlusUserMap();
		modeUserFunctionsMap['-'] = getMinusUserMap();
    */
	}

	// DOCUMENTATION: https://stackoverflow.com/questions/10876930/should-one-never-use-static-inline-function
	// Static seems to be deprecated in C++
	// Anonymous namespace used for deprecated "static inline".
	namespace {
		/**
		 * 	@brief assing a function using operator [] to a signedMap
		 * 	index.
		 * 
		 *  @param flags A array of chars (the indexes)
		 * 	@param f A pointer to function, that will be assigned to each flags
		 * 	@param amount A integer defining the lenght of @p flags or @p f .
		 * 
		 * 	NOTE: indexes in @p flags and @p f need that mach perform the assignation.
		*/
		inline signedFunctionPointerMap
		for_each_assign(const char*const flags,
		bool (*const f[])(Client* const, Channel* const, std::string&),
		size_t amount)
		throw()
		{
			signedFunctionPointerMap	signedMap;

			for (size_t i = 0 ; i < amount ; i++)
				signedMap[flags[i]] = f[i];

			return (signedMap)
		}
	}

	inline IRCDatabase::signedFunctionPointerMap
    IRCDatabase::getPlusChannelMap()
	{
		signedFunctionPointerMap	signedMap;

        // TO DO: Check if the std::string can be const
        static bool (*const f[])(Client* const, Channel* const, std::string&) = {
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
        static const char flags[] = {
            'O', 'o', 'v', 'a', 'i', 'm', 'n', 'q', 'p', 's', 'r', 't', 'l',
            'k', 'b', 'e', 'I'
        };

		return (for_each_assign(flags, f, sizeof(f) / sizeof(*f)));
	}

	inline IRCDatabase::signedFunctionPointerMap
    IRCDatabase::getMinusChannelMap()
	{
		signedFunctionPointerMap	signedMap;

        // TO DO: Check if the std::string can be const
        static bool (*const f[])(Client* const, Channel* const, std::string&) = {
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
            &removeChannelInviteList
        };

        static const char flags[] = { 'o', 'v', 'a', 'i', 'm', 'n', 'q', 'p'
            's', 'r', 't', 'l', 'k', 'b', 'e', 'I'
        };

		return (for_each_assign(flags, f, sizeof(f) / sizeof(*f)));
	}


// --- User Mode pointer functions --- //

	IRCDatabase::signedFunctionPointerMap	IRCDatabase::getPlusUserMap()
	{
		signedFunctionPointerMap	signedMap;

        static bool (*const f[])(Client* const, Channel* const, std::string&) = {
            &setUserInvisible,
            &setUserServerNotice,
            &setUserWallops,
            &setUserOperator
        };
        static const char flags[] = {'i', 's', 'w', 'o'};

        return (for_each_assign(flags, f, sizeof(f) / sizeof(*f)));
	}

	IRCDatabase::signedFunctionPointerMap	IRCDatabase::getMinusUserMap()
	{
		signedFunctionPointerMap	signedMap;

        static bool (*const f[])(Client* const, Channel* const, std::string&) = {
            &unsetUserInvisible,
            &unsetUserServerNotice,
            &unsetUserWallops,
            &unsetUserOperator
        };
        static const char flags[] = {'i', 's', 'w', 'o'};

        return (for_each_assign(flags, f, sizeof(f) / sizeof(*f)));
	}
}