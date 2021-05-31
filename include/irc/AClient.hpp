#pragma once

#include <irc/ircdef.hpp>

#include <irc/ABufferedConnection.hpp>

#include <irc/AMessage.hpp>

#include <irc/PrivateMessage.hpp>
#include <irc/replies/IReply.hpp>
//#include <irc/Channel.hpp>
//#include <irc/Server.hpp>

#include <string>
#include <map>
#include <stdint.h>

#include <utils/BitField.hpp>
#include <utils/strings.hpp>

#include <ostream>

namespace NAMESPACE_IRC
{
	class Channel;
	struct Database;

	class AClient	:	public ABufferedConnection
	{
	private:
		typedef std::map<std::string, Channel*>			channelMap;
		typedef std::pair<std::string, Channel*>		channelPair;

	public:
		enum	Mode
		{
			i = (1 << 0),
			s = (1 << 1),
			w = (1 << 2),
			/// Operator
			o = (1 << 3)
		};

		/**
		 * @brief Binary user modes.
		 */
		BitField<Mode, uint32_t>	modes;

		/// An unique nickname acting as the user's identifier.
		/// Only characters from the nickname charset are allowed.
		/// Uniqueness is case-insensitive.
		std::string	nickname;
		/// The previous nickname.
		std::string	oldNickname;
		/// The user's hostname.
		/// Not to be set by users! Only set by servers in server to server communication.
		std::string	hostname;
		std::string	username;
		/// The name of the server the client is connected to.
		/// Not to be set by users! Only set by servers in server to server communication.
		std::string	servername;
		/// The user's real name. Special characters are allowed.
		std::string	realname;

		/**
		 * @brief Authentication state.
		 * The user is authenticated when there is no password set,
		 * or the password was verified using the PASS command.
		 */
		bool		authenticated;

		/**
		 * @brief Registration state.
		 * The user is authenticated when he successfully registers using the
		 * USER command.
		 */
		bool		registered;

		/**
		 * @brief A map of channels by name the user is connected to.
		 */
		channelMap	channels;

		AClient(bool authRequired = true);


		virtual ~AClient() throw()
		{ leaveAllChannels(); };

		/**
		 * @brief Send a message to the user using the underlying connection.
		 */
		AClient&	operator<<(IReply const& message)
		{ ABufferedConnection::operator<<(message); return *this; };

		AClient&	operator<<(std::string const& message)
		{ ABufferedConnection::operator<<(message); return *this; }

		virtual bool	isLocal() const throw() = 0;

		void	becomeOperator() throw()
		{ modes.set(o); }

		bool	isOperator() const throw()
		{ return modes[o]; }

		void	welcome(Database const& database);

		void	joinChannel(Channel* const channel);
		void	leaveChannel(Channel* const channel);
		void	leaveChannel(std::string const& channelName);
		void	leaveAllChannels();

		bool	isInChannel(Channel* const channel) const;
		bool	isInChannel(std::string const& channelName) const
		{ return channels.find(ft::strToLower(channelName)) != channels.end(); };

		bool	isInSameChannel(AClient const* client) const;

		Channel	*getChannel(std::string const& channelName) const;
//		Channel	*getChannelGlobal(Database const& db, std::string const& channelName) const;
				// getChannel() + channel in the database if it's neither private nor secret

		void	receiveMessage(AClient const* client, std::string const &message)
		{ *this << PrivateMessage(client->nickname, message); };

		bool	listChannelInfo(Channel* const channel);
		bool	listAllChannelsListInfo(Database const& db);

		bool	listChannelWhoQueryInfo(Channel* const channel, int opFlag);
		bool	listAllVisibleUsersWhoQueryInfo(Database const& db);
		bool	matchMaskWhoQueryInfo(Database const& db, std::string const &mask);

		//AClient&	operator<<(IReply const& str);
	};
}
