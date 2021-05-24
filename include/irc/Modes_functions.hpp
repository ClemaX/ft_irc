
# pragma once

//# include <irc/Channel.hpp>
# include <irc/ircdef.hpp>

namespace NAMESPACE_IRC
{
	// What are the templates for if we still use the forward declarations?
	class Server;
	class AClient;
	template <class __Server, class __Client>
	class Channel;

	////////////////
	// User modes //
	////////////////

	typedef Channel<Server, AClient> __Channel;

	bool	setUserInvisible(AClient* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetUserInvisible(AClient* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setUserServerNotice(AClient* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetUserServerNotice(AClient* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setUserWallops(AClient* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetUserWallops(AClient* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setUserOperator(AClient* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetUserOperator(AClient* const user, __Channel *const channel, const std::string& flagArguments);

	///////////////////
	// Channel modes //
	///////////////////

	bool	addChannelCreator(AClient* const user, __Channel *const channel, const std::string& flagArguments);

	bool	addChannelOperator(AClient* const user, __Channel *const channel, const std::string& flagArguments);
	bool	removeChannelOperator(AClient* const user, __Channel *const channel, const std::string& flagArguments);

	bool	addChannelVoice(AClient* const user, __Channel *const channel, const std::string& flagArguments);
	bool	removeChannelVoice(AClient* const user, __Channel *const channel, const std::string& flagArguments);


	bool	setChannelAnonymous(AClient* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetChannelAnonymous(AClient* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setChannelInviteOnly(AClient* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetChannelInviteOnly(AClient* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setChannelModerated(AClient* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetChannelModerated(AClient* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setChannelNoExternalMessage(AClient* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetChannelNoExternalMessage(AClient* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setChannelQuiet(AClient* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetChannelQuiet(AClient* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setChannelPrivate(AClient* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetChannelPrivate(AClient* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setChannelSecret(AClient* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetChannelSecret(AClient* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setChannelReop(AClient* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetChannelReop(AClient* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setChannelRestrictTopic(AClient* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetChannelRestrictTopic(AClient* const user, __Channel *const channel, const std::string& flagArguments);

	bool	setChannelLimit(AClient* const user, __Channel *const channel, const std::string& flagArguments);
	bool	unsetChannelLimit(AClient* const user, __Channel *const channel, const std::string& flagArguments);

	bool	addChannelKey(AClient* const user, __Channel *const channel, const std::string& flagArguments);
	bool	removeChannelKey(AClient* const user, __Channel *const channel, const std::string& flagArguments);


	bool	addChannelBanned(AClient* const user, __Channel *const channel, const std::string& flagArguments);
	bool	removeChannelBanned(AClient* const user, __Channel *const channel, const std::string& flagArguments);

	bool	addChannelException(AClient* const user, __Channel *const channel, const std::string& flagArguments);
	bool	removeChannelException(AClient* const user, __Channel *const channel, const std::string& flagArguments);

	bool	addChannelInviteList(AClient* const user, __Channel *const channel, const std::string& flagArguments);
	bool	removeChannelInviteList(AClient* const user, __Channel *const channel, const std::string& flagArguments);
}
