
# pragma once

//# include <irc/Channel.hpp>
# include <irc/ircdef.hpp>

namespace NAMESPACE_IRC
{

	class Server;
	class Client;
	template <class __Server, class __Client>
	class Channel;

	////////////////
	// User modes //
	////////////////

	typedef Channel<Server, Client> __Channel;

	bool	setUserInvisible(Client* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetUserInvisible(Client* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setUserServerNotice(Client* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetUserServerNotice(Client* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setUserWallops(Client* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetUserWallops(Client* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setUserOperator(Client* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetUserOperator(Client* const user, __Channel *const channel, const std::string& flagArguments);

	///////////////////
	// Channel modes //
	///////////////////

	bool	addChannelCreator(Client* const user, __Channel *const channel, const std::string& flagArguments);

	bool	addChannelOperator(Client* const user, __Channel *const channel, const std::string& flagArguments);
	bool	removeChannelOperator(Client* const user, __Channel *const channel, const std::string& flagArguments);

	bool	addChannelVoice(Client* const user, __Channel *const channel, const std::string& flagArguments);
	bool	removeChannelVoice(Client* const user, __Channel *const channel, const std::string& flagArguments);


	bool	setChannelAnonymous(Client* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetChannelAnonymous(Client* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setChannelInviteOnly(Client* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetChannelInviteOnly(Client* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setChannelModerated(Client* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetChannelModerated(Client* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setChannelNoExternalMessage(Client* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetChannelNoExternalMessage(Client* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setChannelQuiet(Client* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetChannelQuiet(Client* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setChannelPrivate(Client* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetChannelPrivate(Client* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setChannelSecret(Client* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetChannelSecret(Client* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setChannelReop(Client* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetChannelReop(Client* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setChannelRestrictTopic(Client* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetChannelRestrictTopic(Client* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setChannelLimit(Client* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetChannelLimit(Client* const user, __Channel *const channel, const std::string& flagArguments);

	bool	addChannelKey(Client* const user, __Channel *const channel, const std::string& flagArguments);
	bool	removeChannelKey(Client* const user, __Channel *const channel, const std::string& flagArguments);


	bool	addChannelBanned(Client* const user, __Channel *const channel, const std::string& flagArguments);
	bool	removeChannelBanned(Client* const user, __Channel *const channel, const std::string& flagArguments);

	bool	addChannelException(Client* const user, __Channel *const channel, const std::string& flagArguments);
	bool	removeChannelException(Client* const user, __Channel *const channel, const std::string& flagArguments);

	bool	addChannelInviteList(Client* const user, __Channel *const channel, const std::string& flagArguments);
	bool	removeChannelInviteList(Client* const user, __Channel *const channel, const std::string& flagArguments);
}
