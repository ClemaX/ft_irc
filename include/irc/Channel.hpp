#pragma once

#include <map> // using std::map
#include <set> // using std::set

#include <iostream> // using std::cout // for testing for now

#include <irc/Client.hpp>
#include <irc/Server.hpp>
#include <utils/strings.hpp>

#include <stdint.h> // fast, portable, secure types (C++11 cstdint)

namespace irc
{
	class Server;
	class Client;
	// TODO: Reference to connection and add ChannelClient on JOIN command
	struct	ChannelClient
	{
		Client*	client;

		ChannelClient();
		ChannelClient(Client* client);
		ChannelClient(Client* client, bool isOp);
		ChannelClient(const ChannelClient & src);

		~ChannelClient();

		ChannelClient & operator=(const ChannelClient & src);
	};

	/**
	 * 	@brief Hodl all avalaible channel modes
	 *
	 *	O - give "channel creator" status;
     *	o - give/take channel operator privilege;
     *	v - give/take the voice privilege;
	 *
	 *	a - toggle the anonymous channel flag;
     *	i - toggle the invite-only channel flag;
     *	m - toggle the moderated channel;
     *	n - toggle the no messages to channel from clients on the outside;
  	 *	q - toggle the quiet channel flag;
     *	p - toggle the private channel flag;
     *	s - toggle the secret channel flag;
 	 *	r - toggle the server reop channel flag;
     *	t - toggle the topic settable by channel operator only flag;
	 *
     *	k - set/remove the channel key (password);
     *	l - set/remove the user limit to channel;
	 *
     *	b - set/remove ban mask to keep users out;
 	 *	e - set/remove an exception mask to override a ban mask;
 	 *	I - set/remove an invitation mask to automatically override the invite-only flag;
	*/
	struct	ChannelModes
	{

		typedef std::map<std::string, std::string> channelNicknameMap; // old

		typedef std::map<std::string, uint32_t> ModesMap;

		# define	M_a (1 << 0)
		# define	M_i (1 << 1)
		# define	M_m (1 << 2)
		# define	M_n (1 << 3)
		# define	M_q (1 << 4)
		# define	M_p (1 << 5)
		# define	M_s (1 << 6)
		# define	M_r (1 << 7)
		# define	M_t (1 << 8)

		# define	M_O (1 << 9)
		# define	M_o (1 << 10)
		# define	M_v (1 << 11)
		# define	M_b (1 << 12)
		# define	M_e (1 << 13)
		# define	M_I (1 << 14)

		ModesMap		modesMap;

		// TO DO: Change this to a unique map<std::string, uint32_t>
		// Use flags (1 << {9 to 14}) {OovbeI} for uint32_t.
		channelNicknameMap	O;
		channelNicknameMap	o;
		channelNicknameMap	v;

		uint32_t	binMode;

		size_t	l;
		std::string	k;

		// TO DO: (same as prev todo) Change this to a unique map<std::string, uint32_t>
		channelNicknameMap	b;
		channelNicknameMap	e;
		channelNicknameMap	I;

		ChannelModes();
		~ChannelModes();

	};

	class	Channel
	{

	public:
		typedef std::map<Client*, ChannelClient> channelClientMap;
		typedef std::map<Server*, Server*> channelServerMap;
		typedef std::map<std::string, std::string> channelNicknameMap;

		class	ChannelException		:	public std::exception { };

		class	InvalidChannelNameException	:	public ChannelException
		{
			public: char const*	what() const throw()
			{ return "Invalid channel name"; };
		};

	private:
		Channel();
		std::string	setChannelName(std::string channelName);

	public:
		channelClientMap	clientsMap;
		channelServerMap	serversMap;
		std::string			topic;

		ChannelModes		channelModes;
		std::string const			name;

		char				channelType;

		Channel(std::string const& channelName) throw(InvalidChannelNameException);
		~Channel();

		Channel const&	operator<<(NumericReply const& reply);
		Channel const&	operator<<(PrivateMessage const& reply);

	// Get functions
		std::string	getTopic() const;
		Client *getUser(std::string const & clientNickname) const;

	// Set functions
		void	setTopic(const std::string & str);

	// Check functions
		bool	checkChannelName(const std::string &str) const;

		bool	isInChannel(Client *client) const;
		bool	isInChannel(std::string const & clientNickname) const;

		bool	isVisibleForClient(Client *client) const;

		bool	isOperator(Client *client) const;						// also check for Creators
		bool	isOperator(std::string const & clientNickname) const;	// also check for Creators

		bool	isCreator(Client *client) const;
		bool	isCreator(std::string const & clientNickname) const;

		bool	isStatusVoice(Client *user) const;
		bool	isStatusBanned(Client *user) const;
		bool	isStatusException(Client *user) const;
		bool	isStatusInvite(Client *user) const;

		bool	isLocalChannel(void) const;
		bool	isNetworkChannel(void) const;
		bool	isNetworkSafeChannel(void) const;
		bool	isNetworkUnmoderatedChannel(void) const;

		bool	isLocalChannelVisibleForClient(Client const *client) const;

	// Message


	// Message / Notice
		void	receiveMessage(Client *client, std::string const &message);
		void	receiveNotice(Client *client, std::string const &message);

	// Add/Remove functions
		bool	addClient(Client* client, std::string & password, bool	isChannelOperator = false);
		bool	addServer(Server* server);

		bool	removeClient(Client* client, std::string const &leaveMessage);

		bool	close();

		/* Handle mods */

		bool	addCreator(const std::string& nickname);
		bool	removeCreator(const std::string& nickname);

		bool	addOperator(const std::string& nickname);
		bool	removeOperator(const std::string& nickname);

		bool	addVoice(const std::string& nickname);
		bool	removeVoice(const std::string& nickname);


		bool	addBanned(const std::string& nickname);
		bool	removeBanned(const std::string& nickname);

		bool	addException(const std::string& nickname);
		bool	removeException(const std::string& nickname);

		bool	addInviteList(const std::string& nickname);
		bool	removeInviteList(const std::string& nickname);

	};

}
