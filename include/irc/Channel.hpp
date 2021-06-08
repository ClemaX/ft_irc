#pragma once

#include <map> // using std::map
#include <set> // using std::set

#include <iostream> // using std::cout // for testing for now

//#include <irc/AClient.hpp>
#include <irc/AMessage.hpp>
#include <irc/Server.hpp>
#include <utils/strings.hpp>

#include <utils/BitField.hpp>

#include <irc/replies/ErrorReplies.hpp>
#include <irc/replies/NumericReply.hpp>
#include <irc/replies/CommandReplies.hpp>
#include <irc/PrivateMessage.hpp>

#include <stdint.h> // fast, portable, secure types (C++11 cstdint)

namespace NAMESPACE_IRC
{
	/// global Host Name
	extern std::string gHostname;

	// TODO: Reference to connection and add ChannelClient on JOIN command

	template <class __Client>
	struct	ChannelClient // IN WHICH WAY THIS CLASS CAN HAVE AN USE ?
	{
		__Client*	client;

		ChannelClient();
		ChannelClient(__Client* const client);
		ChannelClient(__Client* const client, bool isOp);
		ChannelClient(const ChannelClient& src);

		~ChannelClient();

		ChannelClient & operator=(const ChannelClient & src);
	};

	/**
	 * 	@brief Hodl all avalaible channel modes:
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

	template <class __Server, class __Client>
	class Channel
	{
		/* Member types */

		public:


		enum Mode
		{
			a = (1 << 0),
			i = (1 << 1),
			m = (1 << 2),
			n = (1 << 3),
			q = (1 << 4),
			p = (1 << 5),
			s = (1 << 6),
			r = (1 << 7),
			t = (1 << 8),
			O = (1 << 9),
			o = (1 << 10),
			v = (1 << 11),
			b = (1 << 12),
			e = (1 << 13),
			I = (1 << 14)
		};

		struct	ChannelModes	: BitField<Mode, uint32_t>
		{
		public:
			typedef std::map<std::string, uint32_t> ModesMap;

			ModesMap		channelModes; // TO DO: remane to 'UsersInChannelModes'
			size_t			l;
			std::string		k;

			ChannelModes();

			ChannelModes& operator=(uint32_t modes)
			{ BitField<Mode, uint32_t>::operator=(modes); return *this; }

		};

		typedef typename std::map<__Client*, ChannelClient<__Client> >	channelClientMap;
		typedef typename std::map<__Server*, __Server*>					channelServerMap;

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

		Channel const&	operator<<(IReply const& reply);
		Channel const&	operator<<(PrivmsgChannelMessage const& reply);
		//Channel const&	operator<<(PrivateMessage const& reply);

		/* Getters */

		const std::string&	getTopic() const;
		__Client*			getUser(const std::string& clientNickname) const;

		/* Setters  */

		void	setTopic(const std::string & str);

		/* Booleans */

		bool	checkChannelName(const std::string &str) const;

		bool	isInChannel(__Client*const client) const;
		bool	isInChannel(const std::string& clientNickname) const;

		bool	isVisibleForClient(__Client*const client) const;

		bool	isOperator(__Client const* client) const;						// also check for Creators
		bool	isOperator(const std::string& clientNickname) const;	// also check for Creators

		bool	isCreator(__Client const* client) const;
		bool	isCreator(const std::string& clientNickname) const;

		bool	isStatusVoice(__Client const* user) const;
		bool	isStatusBanned(__Client const* user) const;
		bool	isStatusException(__Client const* user) const;
		bool	isStatusInvite(__Client const* user) const;

		bool	isLocalChannel(void) const;
		bool	isNetworkChannel(void) const;
		bool	isNetworkSafeChannel(void) const;
		bool	isNetworkUnmoderatedChannel(void) const;

		bool	isLocalChannelVisibleForClient(__Client const* client) const;

		/* Message / Notice */

		void	receiveMessage(__Client*const client, std::string const &message);
		void	receiveNotice(__Client *const client, std::string const &message);

		/* Modifiers */

		bool	addClient(__Client*const client, std::string& password, bool isChannelOperator = false);
		bool	addServer(__Server*const server);

		bool	removeClient(__Client*const client, std::string const &leaveMessage);
		bool	kickClient(__Client* const kicker, __Client* const victim, std::string kickMessage);

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

	template <class __Client>
	inline
	ChannelClient<__Client>::
	ChannelClient()
	{ }

	template <class __Client>
	inline
	ChannelClient<__Client>::
	ChannelClient(__Client* const client, bool isOp)
	: client(client)
	{ static_cast<void>(isOp); }

	template <class __Client>
	inline
	ChannelClient<__Client>::
	ChannelClient(__Client* const client)
	: client(client)
	{ }

	template <class __Client>
	inline
	ChannelClient<__Client>::
	ChannelClient(const ChannelClient& src)
	{ *this = src; }

	template <class __Client>
	inline
	ChannelClient<__Client>::
	~ChannelClient()
	{ }

	template <class __Client>
	inline
	ChannelClient<__Client>&
	ChannelClient<__Client>::
	operator=(const ChannelClient& src)
	{
		client = src.client;
		return (*this);
	}

	/////////////////////
	// Channel members //
	/////////////////////

	template <class __Server, class __Client>
	inline
	Channel<__Server, __Client>::ChannelModes::ChannelModes()
	{ }

	template <class __Server, class __Client>
	Channel<__Server, __Client>::
	Channel(std::string const& channelName)
	throw(InvalidChannelNameException)
	: name(setChannelName(channelName))
	{
		if (checkChannelName(name) == false)
			throw InvalidChannelNameException();
		else if (isNetworkUnmoderatedChannel())
			channelModes = Channel::m | Channel::t;
	}

	template <class __Server, class __Client>
	inline
	Channel<__Server, __Client>::
	~Channel()
	{ }

	template <class __Server, class __Client>
	Channel<__Server, __Client> const&
	Channel<__Server, __Client>::
	operator<<(IReply const& message)
	{
		for (typename Channel::channelClientMap::iterator it = clientsMap.begin() ; it != clientsMap.end() ; it++)
			*it->first << message;
		return (*this);
	}

	template <class __Server, class __Client>
	Channel<__Server, __Client> const&
	Channel<__Server, __Client>::
	operator<<(PrivmsgChannelMessage const& message)
	{
		for (typename Channel::channelClientMap::iterator it = clientsMap.begin() ; it != clientsMap.end() ; it++)
		{
			if (message.prefix.name != it->first->nickname)
				*it->first << message;
		}
		return (*this);
	}

	/* template <class __Server, class __Client>
	Channel<__Server, __Client> const&
	Channel<__Server, __Client>::
	operator<<(PrivateMessage const& reply)
	{
		for (typename Channel::channelClientMap::iterator it = clientsMap.begin() ; it != clientsMap.end() ; it++)
			*it->first << reply;
		return (*this);
	} */

	/////////////
	// Getters //
	/////////////

	template <class __Server, class __Client>
	inline const std::string&
	Channel<__Server, __Client>::
	getTopic() const
	{ return (topic); }

	template <class __Server, class __Client>
	__Client*
	Channel<__Server, __Client>::
	getUser(std::string const& clientNickname) const
	{
		for (typename channelClientMap::const_iterator it = clientsMap.begin()
		; it != clientsMap.end(); it++)
			if (it->first->nickname == clientNickname)
				return (it->first);
		return (NULL);
	}

	/////////////
	// Setters //
	/////////////

	template <class __Server, class __Client>
	inline void
	Channel<__Server, __Client>::
	setTopic(const std::string& str)
	{ topic = str; }

	template <class __Server, class __Client>
	std::string
	Channel<__Server, __Client>::
	setChannelName(const std::string& channelName)
	{
		if (!isNetworkSafeChannel())
			return (ft::strToLower(channelName));

		std::string str = ft::strToLower(channelName);
		channelType = str.at(0);

		std::string prefix;
		srand (time(NULL));
		static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz0123456789";
		for (size_t i = 0 ; i < 5UL ; i++)
			prefix.push_back(alphanum[rand() % ARRAY_SIZE(alphanum)]);
		str.insert(1, prefix);
		return (str);
	}

	//////////////
	// Booleans //
	//////////////

	template <class __Server, class __Client>
	bool
	Channel<__Server, __Client>::
	checkChannelName(const std::string& str) const
	{
		return (!((str.length() < 2UL || str.length() > 50UL)
		|| (str.at(0) != '&' && str.at(0) != '#' && str.at(0) != '+' && str.at(0) != '!')
		|| (str.find(' ') != std::string::npos || str.find(',') != std::string::npos || str.find('\'') != std::string::npos)));
	}

	template <class __Server, class __Client>
	bool
	Channel<__Server, __Client>::
	isInChannel(std::string const& clientNickname) const
	{
		for (typename channelClientMap::const_iterator it = clientsMap.begin(); it != clientsMap.end(); it++)
			if (it->first->nickname == clientNickname)
				return (true);
		return (false);
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isInChannel(__Client*const client) const
	{ return (clientsMap.find(client) != clientsMap.end()); }

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

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isOperator(__Client const* client) const
	{ return (check_user_mod(channelModes.channelModes, client->nickname, Channel::O | Channel::o)); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isCreator(__Client const* client) const
	{ return (check_user_mod(channelModes.channelModes, client->nickname, Channel::O)); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isStatusVoice(__Client const* user) const
	{ return (check_user_mod(channelModes.channelModes, user->nickname, Channel::v)); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isStatusBanned(__Client const* user) const
	{ return (check_user_mod(channelModes.channelModes, user->nickname, Channel::b)); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isStatusException(__Client const* user) const
	{ return (check_user_mod(channelModes.channelModes, user->nickname, Channel::e)); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isStatusInvite(__Client const* user) const
	{ return (check_user_mod(channelModes.channelModes, user->nickname, Channel::i)); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isLocalChannelVisibleForClient(__Client const* client) const
	{
		(void)client;
		return (true); // !isLocalChannel() || client->isLocal()
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isVisibleForClient(__Client*const client) const
	{ return (isInChannel(client) || (!(channelModes & (Channel::p | Channel::s))
	&& isLocalChannelVisibleForClient(client))); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isOperator(const std::string& clientNickname) const
	{ return (check_user_mod(channelModes.channelModes, clientNickname, Channel::O | Channel::o)); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isCreator(const std::string& clientNickname) const
	{ return (check_user_mod(channelModes.channelModes, clientNickname, Channel::O)); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isLocalChannel(void) const
	{ return (channelType == '&'); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isNetworkChannel(void) const
	{ return (channelType == '#'); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isNetworkSafeChannel(void) const
	{ return (channelType == '!'); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isNetworkUnmoderatedChannel(void) const
	{ return (channelType == '+'); }

	//////////////////////
	// Message / Notice //
	//////////////////////

	template <class __Server, class __Client>
	void
	Channel<__Server, __Client>::
	receiveMessage(__Client *const client, std::string const& message)
	{
		if ((!isInChannel(client) && channelModes & Channel::n)
		|| (channelModes & Channel::m && !isStatusVoice(client) && !isOperator(client))
		|| (isStatusBanned(client)))
			*client << CannotSendToChanError(gHostname, name);
		else
			*this << PrivmsgChannelMessage(client->nickname, name, message);
	}

	template <class __Server, class __Client>
	void
	Channel<__Server, __Client>::
	receiveNotice(__Client*const client, std::string const& message)
	{
		if (!((!isInChannel(client) && channelModes & Channel::n)
		|| (channelModes & Channel::m && !isStatusVoice(client) && !isOperator(client))
		|| (isStatusBanned(client))))
			*this << PrivateMessage(client->nickname, message);
	}

	///////////////
	// Modifiers //
	///////////////

	template <class __Server, class __Client>
	bool
	Channel<__Server, __Client>::addClient(__Client*const client, std::string& password, bool isChannelOperator)
	{
		if (clientsMap.find(client) != clientsMap.end())
			return (false);
		if (channelModes.l > 0 && clientsMap.size() >= channelModes.l)
		{
			*client << ChannelIsFullError(gHostname, name);
			return (false);
		}
		if (isStatusBanned(client) && !isStatusException(client))
		{
			*client << BannedFromChanError(gHostname, name);
			return (false);
		}
		if ((channelModes & Channel::i) && !isStatusInvite(client))
		{
			*client << InviteOnlyChanError(gHostname, name);
			return (false);
		}
		if (channelModes.k.compare("") && channelModes.k == password)
		{
			*client << BadChannelKeyError(gHostname, name);
			return (false);
		}
		clientsMap[client] = ChannelClient<AClient>(client, isChannelOperator); // NEED THIS ?!?!
		channelModes.channelModes.insert(std::pair<std::string, uint32_t>(client->nickname, 0));
		if (isNetworkSafeChannel() && clientsMap.size() == 1UL) // [WARNING!] THIS LINE WAS EDDITED
			addCreator(client->nickname);
		else if (isChannelOperator)
			addOperator(client->nickname);
		client->joinChannel(this);
		*this << JoinChannelMessage(client->nickname, name);
		*client << TopicReply(gHostname, name, topic);
		*client << ChannelNamesReply(gHostname, this);

		return true;
	}

	template <class __Server, class __Client>
	bool
	Channel<__Server, __Client>::
	addServer(__Server* const server)
	{
		const typename Channel::channelServerMap::iterator& it = serversMap.find(server);
		if (it != serversMap.end())
			return (false);
		serversMap[server] = server;
		return (true);
	}

	template <class __Server, class __Client>
	bool
	Channel<__Server, __Client>::
	removeClient(__Client* const client, std::string const& leaveMessage)
	{
		const typename Channel::channelClientMap::iterator& it = clientsMap.find(client);
		if (it == clientsMap.end())
			return (false);
		*this << LeaveChannelMessage(client->nickname, name, leaveMessage);
		client->leaveChannel(this);
		clientsMap.erase(it);
		if (clientsMap.empty())
			return (close());
		return (true);
	}

	template <class __Server, class __Client>
	bool
	Channel<__Server, __Client>::
	kickClient(__Client* const kicker, __Client* const victim, std::string kickMessage)
	{
		const typename Channel::channelClientMap::iterator& it = clientsMap.find(victim);
		if (it == clientsMap.end())
			return (false);
		*this << KickChannelMessage(kicker->nickname, victim->nickname, name, kickMessage);
		victim->leaveChannel(this);
		clientsMap.erase(it);
		if (clientsMap.empty())
			return (close());
		return (true);
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	close()
	{
		if (serversMap.empty() == false)
			serversMap.begin()->second->database.dataChannelsMap.erase(name);
		delete this;
		return (true);
	}

	/////////////////
	// Handle mods //
	/////////////////

	namespace
	{
		template <class __Reply, class __Channel>
		inline bool
		user_in_channel(const std::string& nickname, __Channel* const c)
		{
			if (!c->isInChannel(nickname))
			{
				__Reply(gHostname, nickname, c->name);
				return (false);
			}
			return (true);
		}

		template <class __Reply, class Map, class __Channel>
		bool
		add_mode(Map& m, __Channel* const c, const std::string& key, size_t mask,
		const char*const mode_msg)
		{
			const typename Map::iterator& it = m.find(key);
			if (it != m.end())
			{
				it->second |= mask;
				*c << __Reply(gHostname, c->name, mode_msg, key);
				return (true);
			}
			return (false);
		}

		template <class __Reply, class Map, class __Channel>
		bool
		reset_mode(Map& m, __Channel* const c, const std::string& key, size_t mask,
		const char*const mode_msg)
		{
			const typename Map::iterator& it = m.find(key);
			if (it != m.end())
			{
				it->second &= ~mask;
				*c << __Reply(gHostname, c->name, mode_msg, key);
				return (true);
			}
			return (false);
		}
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	addCreator(const std::string& nickname)
	{
		return (user_in_channel<UserNotInChannelError>(nickname, this)
		&& add_mode<ChannelModeIsReply>(channelModes.channelModes, this, nickname, Channel::O, "+O"));
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	removeCreator(const std::string& nickname)
	{
		return (user_in_channel<UserNotInChannelError>(nickname, this)
		&& reset_mode<ChannelModeIsReply>(channelModes.channelModes, this, nickname, Channel::O, "-O"));
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	addOperator(const std::string& nickname)
	{
		return (user_in_channel<UserNotInChannelError>(nickname, this)
		&& add_mode<ChannelModeIsReply>(channelModes.channelModes, this, nickname, Channel::o, "+o"));
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	removeOperator(const std::string& nickname)
	{
		return (user_in_channel<UserNotInChannelError>(nickname, this)
		&& reset_mode<ChannelModeIsReply>(channelModes.channelModes, this, nickname, Channel::o, "-o"));
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	addVoice(const std::string& nickname)
	{
		return (user_in_channel<UserNotInChannelError>(nickname, this)
		&& add_mode<ChannelModeIsReply>(channelModes.channelModes, this, nickname, Channel::v, "+v"));
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	removeVoice(const std::string& nickname)
	{
		return (user_in_channel<UserNotInChannelError>(nickname, this)
		&& reset_mode<ChannelModeIsReply>(channelModes.channelModes, this, nickname, Channel::v, "-v"));
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	addBanned(const std::string& nickname)
	{ return (add_mode<BanListReply>(channelModes.channelModes, this, nickname, Channel::b, "+")); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	removeBanned(const std::string& nickname)
	{ return (reset_mode<BanListReply>(channelModes.channelModes, this, nickname, Channel::b, "-")); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	addException(const std::string& nickname)
	{ return (add_mode<ExceptionListReply>(channelModes.channelModes, this, nickname, Channel::e, "+")); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	removeException(const std::string& nickname)
	{ return (reset_mode<ExceptionListReply>(channelModes.channelModes, this, nickname, Channel::e, "-")); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	addInviteList(const std::string& nickname)
	{ return (add_mode<InviteListReply>(channelModes.channelModes, this, nickname, Channel::I, "+")); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	removeInviteList(const std::string& nickname)
	{ return (reset_mode<InviteListReply>(channelModes.channelModes, this, nickname, Channel::I, "-")); }
}
