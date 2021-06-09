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
		static const char* const	__modes[];

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
			t = (1 << 8)
		};
		typedef BitField<Mode, uint32_t, t> ModeField;

		enum UserMode
		{
			O = (1 << 0),
			o = (1 << 1),
			v = (1 << 2),
			b = (1 << 3),
			e = (1 << 4),
			I = (1 << 5)
		};
		typedef BitField<UserMode, uint32_t, I> UserModeField;
	
		struct	ChannelModes	: BitField<Mode, uint32_t, t>
		{
		public:
			typedef std::map<std::string, UserModeField> UserModesMap;

			/// Modes by nickname
			UserModesMap	userModes;
			/// Maximal users (0 means disabled)
			size_t			l;
			/// Channel password (empty means disabled)
			std::string		k;

			ChannelModes();

			ChannelModes& operator=(uint32_t modes)
			{ ModeField::operator=(modes); return *this; }
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

		std::string getUserModes(const std::string& nickname);

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

		bool	setChannelModesOnCreation(void);

		bool	addClient(__Client*const client, std::string& password, bool isChannelOperator = false, bool newChannel = false);
		bool	addServer(__Server*const server);

		bool	removeClient(__Client*const client, std::string const &leaveMessage);
		bool	kickClient(__Client* const kicker, __Client* const victim, std::string kickMessage);

		bool	close();

		/* Handle mods */

		bool	addCreator(const std::string& sender, const std::string& nickname);
		bool	removeCreator(const std::string& sender, const std::string& nickname);

		bool	addOperator(const std::string& sender, const std::string& nickname, bool displayMessage);
		bool	removeOperator(const std::string& sender, const std::string& nickname);

		bool	addVoice(const std::string& sender, const std::string& nickname);
		bool	removeVoice(const std::string& sender, const std::string& nickname);


		bool	addBanned(const std::string& sender, const std::string& nickname);
		bool	removeBanned(const std::string& sender, const std::string& nickname);

		bool	addException(const std::string& sender, const std::string& nickname);
		bool	removeException(const std::string& sender, const std::string& nickname);

		bool	addInviteList(const std::string& sender, const std::string& nickname);
		bool	removeInviteList(const std::string& sender, const std::string& nickname);

	};

	// 10 chars* per line starting at {1, 1}
	template<typename Server, typename Client>
	const char* const Channel<Server, Client>::__modes[] = {
		0,
		"a", "i", 0, "m", 0, 0, 0, "n", 0, 0,
		0, 0, 0, 0, 0, "q", 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, "p", 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, "s", 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, "r", 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, "t"
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
	{ return (check_user_mod(channelModes.userModes, client->nickname, Channel::O | Channel::o)); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isCreator(__Client const* client) const
	{ return (check_user_mod(channelModes.userModes, client->nickname, Channel::O)); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isStatusVoice(__Client const* user) const
	{ return (check_user_mod(channelModes.userModes, user->nickname, Channel::v)); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isStatusBanned(__Client const* user) const
	{ return (check_user_mod(channelModes.userModes, user->nickname, Channel::b)); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isStatusException(__Client const* user) const
	{ return (check_user_mod(channelModes.userModes, user->nickname, Channel::e)); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isStatusInvite(__Client const* user) const
	{return (check_user_mod(channelModes.userModes, user->nickname, Channel::I));}
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
	{ return (check_user_mod(channelModes.userModes, clientNickname, Channel::O | Channel::o)); }

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	isCreator(const std::string& clientNickname) const
	{ return (check_user_mod(channelModes.userModes, clientNickname, Channel::O)); }

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
	Channel<__Server, __Client>::setChannelModesOnCreation(void)
	{
		channelModes |= __Channel::n;
		channelModes |= __Channel::s;
		return true;
	}

	template <class __Server, class __Client>
	bool
	Channel<__Server, __Client>::addClient(__Client*const client, std::string& password, bool isChannelOperator, bool newChannel)
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
		channelModes.userModes.insert(std::pair<std::string, UserModeField>(client->nickname, UserModeField()));
		if (isNetworkSafeChannel() && clientsMap.size() == 1UL) // [WARNING!] THIS LINE WAS EDDITED
			addCreator(client->nickname, client->nickname);
		else if (isChannelOperator)
			addOperator(client->nickname, client->nickname, newChannel == false);
		client->joinChannel(this);
		*this << JoinChannelMessage(client->nickname, name);
		if (newChannel)
			*client << ModeChannelMessage(gHostname, name, ' ', channelModes.toString(Channel<Server, AClient>::__modes));
		else
			*client << TopicReply(gHostname, name, topic);
		*client << ChannelNamesReply(gHostname, this);
		*client << EndOfNamesReply(gHostname, name);

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

		template <class Map>
		bool
		add_mode(Map& m, const std::string& key, uint32_t mask)
		{
			const typename Map::iterator& it = m.find(key);
			if (it != m.end())
				it->second |= mask;
			else if (mask & Channel<Server, AClient>::I)
				m.insert(std::pair<std::string, Channel<Server, AClient>::UserModeField>(key, Channel<Server, AClient>::UserModeField(mask)));
			else
				return (false);

			return (true);
		}

		template <class Map>
		bool
		reset_mode(Map& m, const std::string& key, size_t mask)
		{
			const typename Map::iterator& it = m.find(key);
			if (it != m.end())
			{
				it->second &= ~mask;

				return (true);
			}
			return (false);
		}
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	addCreator(const std::string& sender, const std::string& nickname)
	{
		bool success = user_in_channel<UserNotInChannelError>(nickname, this)
		&& add_mode(channelModes.userModes, nickname, Channel::O);
		if (success)
			*this << ModeChannelMessage(sender, this->name, '+', "O", nickname);
			// *this << ChannelModeIsReply(sender, nickname, this->name, "+O");
		return success;
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	removeCreator(const std::string& sender, const std::string& nickname)
	{
		bool success = user_in_channel<UserNotInChannelError>(nickname, this)
		&& reset_mode(channelModes.userModes, nickname, Channel::O);
		static_cast<void>(sender);
		// if (success)
		// 	*this << ChannelModeIsReply(sender, this->name, nickname, sender);
		return success;
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	addOperator(const std::string& sender, const std::string& nickname, bool displayMessage)
	{
		bool success = user_in_channel<UserNotInChannelError>(nickname, this)
		&& add_mode(channelModes.userModes, nickname, Channel::o);
		if (success && displayMessage)
			*this << ModeChannelMessage(sender, this->name, '+', "o", nickname);
			// *this << ChannelModeIsReply(sender, nickname, this->name, "+o");
		return success;
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	removeOperator(const std::string& sender, const std::string& nickname)
	{
		bool success = user_in_channel<UserNotInChannelError>(nickname, this)
		&& reset_mode(channelModes.userModes, nickname, Channel::o);
		static_cast<void>(sender);
		// if (success)
		// 	*this << ChannelModeIsReply(sender, this->name, nickname, sender);
		return success;
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	addVoice(const std::string& sender, const std::string& nickname)
	{
		bool success = user_in_channel<UserNotInChannelError>(nickname, this)
		&& add_mode(channelModes.userModes, nickname, Channel::v);
		if (success)
			*this << ModeChannelMessage(sender, this->name, '+', "v", nickname);
			// *this << ChannelModeIsReply(sender, nickname, this->name, "+v");
		return success;
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	removeVoice(const std::string& sender, const std::string& nickname)
	{
		bool success = user_in_channel<UserNotInChannelError>(nickname, this)
		&& reset_mode(channelModes.userModes, nickname, Channel::v);
		static_cast<void>(sender);
		// if (success)
		// 	*this << ChannelModeIsReply(sender, this->name, nickname, sender);
		return success;
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	addBanned(const std::string& sender, const std::string& nickname)
	{
		bool success = add_mode(channelModes.userModes, nickname, Channel::b);
		if (success)
			*this << BanListReply(gHostname, this->name, nickname, sender);
		return success;
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	removeBanned(const std::string& sender, const std::string& nickname)
	{
		bool success = reset_mode(channelModes.userModes, nickname, Channel::b);
		static_cast<void>(sender);
		// if (success)
		// 	*this << BanListReply(gHostname, this->name, nickname, sender);
		return success;
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	addException(const std::string& sender, const std::string& nickname)
	{
		bool success = add_mode(channelModes.userModes, nickname, Channel::e);
		if (success)
			*this << ExceptionListReply(gHostname, this->name, nickname, sender);
		return success;
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	removeException(const std::string& sender, const std::string& nickname)
	{
		bool success = reset_mode(channelModes.userModes, nickname, Channel::e);
		static_cast<void>(sender);
		// if (success)
		// 	*this << ExceptionListReply(gHostname, this->name, nickname, sender);
		return success;
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	addInviteList(const std::string& sender, const std::string& nickname)
	{
		bool success = add_mode(channelModes.userModes, nickname, Channel::I);
		if (success)
			*this << InviteListReply(gHostname, this->name, nickname, sender);
		return success;
	}

	template <class __Server, class __Client>
	inline bool
	Channel<__Server, __Client>::
	removeInviteList(const std::string& sender, const std::string& nickname)
	{
		bool success = reset_mode(channelModes.userModes, nickname, Channel::I);
		static_cast<void>(sender);
		// if (success)
		// 	*this << InviteListReply(gHostname, this->name, nickname, sender);
		return success;
	}
}
