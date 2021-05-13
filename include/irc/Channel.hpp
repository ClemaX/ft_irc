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


	struct	ChannelClient // IN WHICH WAY THIS CLASS CAN HAVE AN USE ?
	{
		Client*	client;

		ChannelClient();
		ChannelClient(Client* const client);
		ChannelClient(Client* const client, bool isOp);
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
		uint32_t		binMode; // Why not only use modesMap;
		size_t			l;
		std::string		k;
	};

	class Channel
	{
		/* Member types */

		public:

		typedef std::map<Client*, ChannelClient>	channelClientMap;
		typedef std::map<Server*, Server*>			channelServerMap;

		struct ChannelException
		: public std::exception
		{ };

		/* Member exeptions */

		struct InvalidChannelNameException
		: public ChannelException
		{ char const* what() const throw() { return ("Invalid channel name"); }; };

		/* Member private */

		private:

		Channel();
		std::string	setChannelName(const std::string& channelName);

		/* Member variables */

		public:

		channelClientMap	clientsMap;
		channelServerMap	serversMap;
		std::string			topic;
		ChannelModes		channelModes;
		const std::string	name;
		char				channelType;

		/* Member functions */

		Channel(std::string const& channelName) throw(InvalidChannelNameException);
		~Channel();

		Channel const&	operator<<(NumericReply const& reply);
		Channel const&	operator<<(PrivateMessage const& reply);

		/* Getters */

		const std::string&	getTopic() const;
		Client*				getUser(const std::string& clientNickname) const;

		/* Setters  */

		void	setTopic(const std::string & str);

		/* Booleans */

		bool	checkChannelName(const std::string &str) const;

		bool	isInChannel(Client* const client) const;
		bool	isInChannel(const std::string& clientNickname) const;

		bool	isVisibleForClient(Client* const client) const;

		bool	isOperator(Client* const client) const;						// also check for Creators
		bool	isOperator(const std::string& clientNickname) const;	// also check for Creators

		bool	isCreator(Client* const client) const;
		bool	isCreator(const std::string& clientNickname) const;

		bool	isStatusVoice(Client* const user) const;
		bool	isStatusBanned(Client* const user) const;
		bool	isStatusException(Client* const user) const;
		bool	isStatusInvite(Client* const user) const;

		bool	isLocalChannel(void) const;
		bool	isNetworkChannel(void) const;
		bool	isNetworkSafeChannel(void) const;
		bool	isNetworkUnmoderatedChannel(void) const;

		bool	isLocalChannelVisibleForClient(Client const *client) const;

		/* Message / Notice */

		void	receiveMessage(Client* const client, std::string const &message);
		void	receiveNotice(Client* const client, std::string const &message);

		/* Modifiers */

		bool	addClient(Client* const client, std::string& password, bool isChannelOperator = false);
		bool	addServer(Server* const server);

		bool	removeClient(Client* const client, std::string const &leaveMessage);

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

	///////////////////////////
	// ChannelClient members //
	///////////////////////////

	inline
	ChannelClient::ChannelClient() { }

	inline
	ChannelClient::ChannelClient(Client* const client, bool isOp)
	: client(client)
	{ static_cast<void>(isOp); }

	inline
	ChannelClient::ChannelClient(Client* const client)
	: client(client)
	{ }

	inline
	ChannelClient::ChannelClient(const ChannelClient& src)
	{ *this = src; }

	inline
	ChannelClient::~ChannelClient()
	{ }

	inline
	ChannelClient&
	ChannelClient::operator=(const ChannelClient& src)
	{
		client = src.client;
		return (*this);
	}

	/////////////////////
	// Channel members //
	/////////////////////

	inline
	Channel::~Channel()
	{ }

	/////////////
	// Getters //
	/////////////

	inline const std::string&
	Channel::getTopic() const
	{ return (topic); }

	/////////////
	// Setters //
	/////////////

	inline void
	Channel::setTopic(const std::string& str)
	{ topic = str; }

	//////////////
	// Booleans //
	//////////////

	inline bool
	Channel::isInChannel(Client* const client) const
	{ return (clientsMap.find(client) != clientsMap.end()); }

	inline bool
	Channel::isVisibleForClient(Client* const client) const
	{ return (isInChannel(client) || (!(channelModes.binMode & (M_p | M_s))
	&& isLocalChannelVisibleForClient(client))); }

	namespace
	{
		template <class Map>
		inline bool
		check_user_mod(const Map& m, const std::string& key, size_t mode_mask)
		{
			const typename Map::const_iterator& it = m.find(key);
			return (it != m.end() && (it->second & mode_mask));
		}
	}

	inline bool
	Channel::isOperator(const std::string& clientNickname) const
	{ return (check_user_mod(channelModes.modesMap, clientNickname, M_O | M_o)); }

	inline bool
	Channel::isCreator(const std::string& clientNickname) const
	{ return (check_user_mod(channelModes.modesMap, clientNickname, M_O)); }

	inline bool
	Channel::isLocalChannel(void) const
	{ return (channelType == '&'); }

	inline bool
	Channel::isNetworkChannel(void) const
	{ return (channelType == '#'); }

	inline bool
	Channel::isNetworkSafeChannel(void) const
	{ return (channelType == '!'); }

	inline bool
	Channel::isNetworkUnmoderatedChannel(void) const
	{ return (channelType == '+'); }

	/////////////////
	// Handle mods //
	/////////////////

	






}
