#include <irc/Database.hpp>
#include <irc/Client.hpp>

namespace irc
{
	IRCDatabase&
	IRCDatabase::operator=(const IRCDatabase& other)
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

	// TO DO: Those 2 are better inlined ...
	// TO DO: Make IRCDatabase template class and fix this !
	void
	IRCDatabase::addChannel(Channel* const channel)
	{ insert_at_value(dataChannelsMap, channel->name, channel); }

	void
	IRCDatabase::addClient(Client* const client)
	{ insert_at_value(dataClientsMap, client->nickname, client); }

	// --- Channel Mode pointer functions --- //

	void
	IRCDatabase::createModeFunctionsMap()
	{
		modeChannelFunctionsMap['+'] = getPlusChannelMap();
		modeChannelFunctionsMap['-'] = getMinusChannelMap();
		modeUserFunctionsMap['+'] = getPlusUserMap();
		modeUserFunctionsMap['-'] = getMinusUserMap();
	}

	// TO DO: Need to be inline ! Is only a return
	// TO DO: Make IRCDatabase template class and fix this !
	IRCDatabase::signedFunctionPointerMap
	IRCDatabase::getPlusChannelMap()
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

	// TO DO: Need to be inline ! Is only a return
	// TO DO: Make IRCDatabase template class and fix this !
	IRCDatabase::signedFunctionPointerMap
	IRCDatabase::getMinusChannelMap()
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


	// --- User Mode pointer functions --- //

	// TO DO: Need to be inline ! Is only a return
	// TO DO: Make IRCDatabase template class and fix this !
	IRCDatabase::signedFunctionPointerMap
	IRCDatabase::getPlusUserMap()
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

	// TO DO: Need to be inline ! Is only a return
	// TO DO: Make IRCDatabase template class and fix this !
	IRCDatabase::signedFunctionPointerMap
	IRCDatabase::getMinusUserMap()
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
