#pragma once

#include <string>

#include <ircdef.hpp>

#include <SocketConnection.hpp>

#include <IRCIReply.hpp>

#include <IRCChannel.hpp>
#include <IRCServer.hpp>

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
		bool	i;
		bool	s;
		bool	w;
		bool	o;

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
		std::string	hostname;
		std::string	username;
		Server	*server;
		ClientModes		clientModes;

		clientChannelMap	clientChannels;


		Client(int fd, address const& address);

		Client const&	operator<<(std::string const& str);

		void	flush() throw(SocketWriteException);

		virtual ~Client() throw();

		void	joinChannel(Channel * channel);
		void	leaveChannel(Channel * channel);
		void	leaveChannel(std::string const & name);
		void	leaveAllChannels();

		bool	isInChannel(Channel *channel) const;
		bool	isInChannel(std::string const & channelName) const;

		Channel	*getChannel(std::string const & channelName) const;
		Channel	*getChannelGlobal(std::string const & channelName) const;
				// getChannel() + channel in the database if it's neither private nor secret
	};
}
