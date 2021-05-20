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

namespace irc
{
	class	Server;
	class	Channel;

	/**
	* In addition to the nickname, all servers must have the
	* following information about all clients: the real name of the host
	* that the client is running on, the username of the client on that
	* host, and the server to which the client is connected.
	*/

	struct	ClientModes
	{
	private:

	public:

		#define	Mu_i 1
		#define	Mu_s 2
		#define	Mu_w 4
		#define	Mu_o 8

		int	binMode;

		// i - marks a users as invisible;
        // s - marks a user for receipt of server notices;
        // w - user receives wallops;
        // o - operator flag.

		ClientModes();
		~ClientModes();

	};

	class	Client	:	public virtual SocketConnection
	{
	private:
		typedef ::std::map<std::string, Channel*>		clientChannelMap;
		typedef ::std::pair<std::string, Channel*>		clientChannelPair;
		typedef IRCDatabase<Server, Client, Channel>	IRCDatabase;

	public:
		std::string	readBuffer;
		std::string	writeBuffer; // TODO: Should we use a Message container instead?

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
		ClientModes		clientModes;

		clientChannelMap	clientChannels;

		/// SocketConnection
		Client(int fd, socketAddress const& address,
			bool authenticationRequired = false);

		Client&	operator<<(std::string const& str);
		Client&	operator<<(IReply const& reply);
		Client&	operator<<(PrivateMessage const& reply);

		void	flush() throw(SocketWriteException);

		virtual ~Client() throw();

		void	joinChannel(Channel * channel);
		void	leaveChannel(Channel * channel);
		void	leaveChannel(std::string const & channelName);
		void	leaveAllChannels();

		bool	isInChannel(Channel *channel) const;
		bool	isInChannel(std::string const & channelName) const;

		bool	isInSameChannel(Client *client) const;

		Channel	*getChannel(std::string const & channelName) const;
		Channel	*getChannelGlobal(std::string const & channelName) const;
				// getChannel() + channel in the database if it's neither private nor secret

		void	receiveMessage(Client *client, std::string const &message);

		bool	listChannelInfo(Channel *channel);
		bool	listAllChannelsListInfo(void);

		bool	listChannelWhoQueryInfo(Channel *channel, int opFlag);
		bool	listAllVisibleUsersWhoQueryInfo(void);
		bool	matchMaskWhoQueryInfo(std::string const &mask);
	};
}
