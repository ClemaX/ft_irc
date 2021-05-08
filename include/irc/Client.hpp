#pragma once

#include <string>

#include <irc/ircdef.hpp>

#include <socket/SocketConnection.hpp>

#include <irc/replies/IReply.hpp>
#include <irc/PrivateMessage.hpp>
#include <irc/replies/NumericReplies.hpp>
#include <irc/replies/CommandReplies.hpp>
#include <irc/replies/ErrorReplies.hpp>

#include <irc/Channel.hpp>
#include <irc/Server.hpp>

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

	class	Client	:	public SocketConnection
	{
	private:
		typedef ::std::map<std::string, Channel*>	clientChannelMap;
		typedef ::std::pair<std::string, Channel*>	clientChannelPair;

	public:
		std::string	readBuffer;
		std::string	writeBuffer; // TODO: Should we use a Message container instead?

		std::string	nickname;
		std::string old_nickname;
		std::string	hostname;
		std::string	username;
		Server	*server;
		ClientModes		clientModes;

		clientChannelMap	clientChannels;



		Client(int fd, address const& address);

		Client const&	operator<<(std::string const& str);
		Client const&	operator<<(NumericReply const& reply);
		Client const&	operator<<(PrivateMessage const& reply);

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
