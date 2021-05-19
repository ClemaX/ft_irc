#include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
// --- NICK --- //
	namespace
	{
		/**
		 * 	@brief Return an avalaible (not collisioned) client nickname,
		 * 	append a '_' for each collision found.
		 *
		 * 	@tparam db A template representing a database that has the
		 * 	member: bool_conversible_type get_client(const std::string&)
		 * 	@param nickname Reseach key.
		 * 	@param database The database where the search will be performed.
		 *
		 * 	@return A valid nickname.
		*/
		template <typename db>
		const std::string&
		set_nickname(const std::string& nickname, const db& database)
		{ return (database.getClient(nickname) ? set_nickname(nickname + "_", database) : nickname); }
		// NOTE: Prev func can be used in the client

	}

	bool
	Server::NickCommand::
	payload(Server& server, Client* user, argumentList const& arguments) const
	{
		// ERR_NONICKNAMEGIVEN No nickname present as args
		if (arguments.empty())
		{
			*user << NoNicknameGivenReply(server.hostname);
			goto error;
		}

		// ERR_ERRONEUSNICKNAME If nickname doesn't follow the format in 2.3.1
		if (nicknameValidator(arguments.at(0)) == 0)
		{
			*user << ErroneusNicknameReply(server.hostname, arguments.at(0));
			goto error;
		}

		// ERR_NICKCOLLISION or ERR_NICKNAMEINUSE
		if (server.database.getClient(arguments.at(0)))
		{
			// ERR_NICKCOLLISION If registered nick is found in another server
			if (user->nickname == IRC_NICKNAME_DEFAULT)
				*user << NickCollisionReply(server.hostname, arguments.at(0),
				user->username, user->hostname);
			// ERR_NICKNAMEINUSE If attemps to change a nickname that is alreaddy in use
			else
				*user << NicknameInUseReply(server.hostname, arguments.at(0));
			goto error;
		}

		user->old_nickname = user->nickname;
		user->nickname = arguments.at(0);

		if (user->old_nickname == IRC_NICKNAME_DEFAULT)
			server.database.addClient(user);
		else
			server.database.set_ClientNick(user->old_nickname, user->nickname);

		server.announceWelcomeSequence(user);

		return (true);

		error:
		return (false);
	}
}

// NICK + USER == Welcome repply NOT only USER
