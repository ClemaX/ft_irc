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

	void
	Server::NickCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{

		if (arguments.empty()) // ERR_NONICKNAMEGIVEN No nickname present as args
			*user << NoNicknameGivenReply(server.hostname);
		else
		{
			std::string const&	newNickname = arguments.at(0);

			if (!nicknameValidator(newNickname)) // ERR_ERRONEUSNICKNAME If nickname doesn't follow the format in 2.3.1
				*user << ErroneusNicknameReply(server.hostname, newNickname);
			else if (server.database.getClient(newNickname)) // ERR_NICKCOLLISION or ERR_NICKNAMEINUSE
			{
				// ERR_NICKCOLLISION If registered nick is found in another server
				if (user->nickname == IRC_NICKNAME_DEFAULT)
					*user << NickCollisionReply(server.hostname, newNickname,
					user->username, user->hostname);
				// ERR_NICKNAMEINUSE If attemps to change a nickname that is alreaddy in use
				else
					*user << NicknameInUseReply(server.hostname, newNickname);
			}
			else
			{
				user->oldNickname = user->nickname;
				user->nickname = newNickname;

				if (user->oldNickname == IRC_NICKNAME_DEFAULT)
					server.database.addClient(user);
				else
				{
					server.database.set_ClientNick(user->oldNickname, user->nickname);
					*user << NickMessage(user->oldNickname, newNickname);
				}

				server.announceWelcomeSequence(user);
			}
		}
	}
}

// NICK + USER == Welcome repply NOT only USER
