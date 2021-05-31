#include <irc/commands/ClientCommands.hpp>

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
		*//*
		const std::string&
		set_nickname(const std::string& nickname, const Database& database)
		{ return (database.getClient(nickname) ? set_nickname(nickname + "_", database) : nickname); }
		// NOTE: Prev func can be used in the client */
	}

	bool
	NickCommand::
	payload(Database& database, AClient* const user, argumentList const& arguments) const
	{
		// ERR_NONICKNAMEGIVEN No nickname present as args
		if (arguments.empty())
		{
			*user << NoNicknameGivenReply(database.hostname);
			goto error;
		}

		// ERR_ERRONEUSNICKNAME If nickname doesn't follow the format in 2.3.1
		if (nicknameValidator(arguments.at(0)) == 0)
		{
			*user << ErroneusNicknameReply(database.hostname, arguments.at(0));
			goto error;
		}

		// ERR_NICKCOLLISION or ERR_NICKNAMEINUSE
		if (database.getClient(arguments.at(0)))
		{
			// ERR_NICKCOLLISION If registered nick is found in another database
			if (user->nickname == IRC_NICKNAME_DEFAULT)
				*user << NickCollisionReply(database.hostname, arguments.at(0),
				user->username, user->hostname);
			// ERR_NICKNAMEINUSE If attemps to change a nickname that is alreaddy in use
			else
				*user << NicknameInUseReply(database.hostname, arguments.at(0));
			goto error;
		}

		user->oldNickname = user->nickname;
		user->nickname = arguments.at(0);

		if (user->oldNickname == IRC_NICKNAME_DEFAULT)
			database.addClient(user);
		else
			database.set_ClientNick(user->oldNickname, user->nickname);

		user->welcome(database);

		return (true);

		error:
		return (false);
	}
}

// NICK + USER == Welcome repply NOT only USER
