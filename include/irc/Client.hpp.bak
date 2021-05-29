#pragma once

#include <string>

#include <irc/ircdef.hpp>

#include <socket/SocketConnection.hpp>
#include <socket/SecureSocketConnection.hpp>

#include <irc/PrivateMessage.hpp>
#include <irc/replies/CommandReplies.hpp>
#include <irc/replies/ErrorReplies.hpp>

#include <irc/Channel.hpp>
#include <irc/Server.hpp>
#include <irc/Database.hpp>

#include <stdint.h>

namespace NAMESPACE_IRC
{
	class	Server;
	template <class __Server, class __Client>
	class	Channel;

	/**
	* In addition to the nickname, all servers must have the
	* following information about all clients: the real name of the host
	* that the client is running on, the username of the client on that
	* host, and the server to which the client is connected.
	*/

	/**
	 * 	@brief Contain the client modes flags:
	 *  i - marks a users as invisible;
     *	s - marks a user for receipt of server notices;
     *	w - user receives wallops;
     * 	o - operator flag.
	*/
	struct	ClientModes
	{
	private:

	public:

		#define	Mu_i (1 << 0)
		#define	Mu_s (1 << 1)
		#define	Mu_w (1 << 2)
		#define	Mu_o (1 << 3)

		uint32_t	binMode;

		ClientModes();

	};

	class	Client	:	public virtual SocketConnection
	{
	private:
		typedef	Channel<Server, Client>					__Channel;
		typedef ::std::map<std::string, __Channel*>		clientChannelMap;
		typedef ::std::pair<std::string, __Channel*>	clientChannelPair;
		typedef IRCDatabase<Server, Client, __Channel>	IRCDatabase;

	public:
		std::string	readBuffer;
		std::string	writeBuffer;

		std::string	nickname;
		std::string old_nickname;
		std::string	hostname;
		std::string	username;
		std::string servername; // 3rd arg USER
		std::string realname; // 4th arg USER

		/// Authentication status set by the PASS command.
		bool		authenticated;

		/// Registered status set by the USER and NICK commands.
		bool		registered;

		Server			*server;
		ClientModes		modes;

		clientChannelMap	channels;

		/// SocketConnection
		Client(int fd, socketAddress const& address,
			bool authenticationRequired = false);

		Client&	operator<<(std::string const& str);
		Client&	operator<<(IReply const& reply);
		Client&	operator<<(PrivateMessage const& reply);

		void	flush() throw(SocketWriteException);

		virtual ~Client() throw();

		void	become_operator();
		bool	is_operator();

		void	joinChannel(__Channel* const channel);
		void	leaveChannel(__Channel* const channel);
		void	leaveChannel(std::string const & channelName);
		void	leaveAllChannels();

		bool	isInChannel(__Channel* const channel) const;
		bool	isInChannel(std::string const & channelName) const;

		bool	isInSameChannel(Client* const client) const;

		__Channel	*getChannel(std::string const & channelName) const;
		__Channel	*getChannelGlobal(std::string const & channelName) const;
				// getChannel() + channel in the database if it's neither private nor secret

		void	receiveMessage(Client* const client, std::string const &message);

		bool	listChannelInfo(__Channel* const channel);
		bool	listAllChannelsListInfo(void);

		bool	listChannelWhoQueryInfo(__Channel* const channel, int opFlag);
		bool	listAllVisibleUsersWhoQueryInfo(void);
		bool	matchMaskWhoQueryInfo(std::string const &mask);
	};

	////////////////////////////
	// Inlined client members //
	////////////////////////////

	inline
	ClientModes::ClientModes()
	: binMode()
	{ }

	inline
	Client::~Client()
	throw()
	{ leaveAllChannels(); }

	inline Client&
	Client::operator<<(std::string const& message)
	{
		writeBuffer.append(message);
		return *this;
	}

	inline Client&
	Client::operator<<(IReply const& reply)
	{
		*this << reply.serialize();
		return *this;
	}

	inline Client&
	Client::operator<<(PrivateMessage const& reply)
	{
		*this << reply.serialize();
		return *this;
	}

	inline void
	Client::flush() throw(SocketWriteException)
	{
		SocketConnection::operator<<(writeBuffer);
		writeBuffer.clear();
	}

	inline bool
	Client::isInChannel(std::string const & channelName) const
	{ return (channels.find(ft::strToLower(channelName)) != channels.end()); }

	inline void
	Client::receiveMessage(Client* const client, std::string const &message)	// check if invisible ?
	{ *this << PrivateMessage(client->nickname, message); }

	inline void
	Client::become_operator()
	{ modes.binMode |= Mu_o; }

	inline bool
	Client::is_operator()
	{ return (modes.binMode & Mu_o); }
}
