#pragma once

#include <map> // using std::map
#include <set> // using std::set

#include <iostream> // using std::cout // for testing for now

#include <irc/AClient.hpp>
#include <irc/AMessage.hpp>

#include <utils/strings.hpp>

#include <utils/BitField.hpp>

#include <irc/PrivateMessage.hpp>

#include <stdint.h> // fast, portable, secure types (C++11 cstdint)


namespace NAMESPACE_IRC
{
	//class AClient;
	/// global Host Name
	extern std::string const&	gHostname;

	// TODO: Reference to connection and add ChannelClient on JOIN command
	struct	ChannelClient // IN WHICH WAY THIS CLASS CAN HAVE AN USE ?
	{
		AClient*	client;

		ChannelClient();
		ChannelClient(AClient* const client);
		ChannelClient(AClient* const client, bool isOp);
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

			ChannelModes()
			{ };

			ChannelModes& operator=(uint32_t modes)
			{ BitField<Mode, uint32_t>::operator=(modes); return *this; }
		};

		typedef std::map<AClient*, ChannelClient >	channelClientMap;
		//typedef std::map<__Server*, __Server*>					channelServerMap;

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
	//	channelServerMap	serversMap;
		std::string			topic;
		ChannelModes		channelModes;
		const std::string	name;
		char				channelType;

		/* Member functions */

		Channel(std::string const& channelName) throw(InvalidChannelNameException);
		~Channel();

		Channel const&	operator<<(IReply const& reply);
		//Channel const&	operator<<(PrivateMessage const& reply);

		/* Getters */

		const std::string&	getTopic() const;
		AClient*			getUser(const std::string& clientNickname) const;

		/* Setters  */

		void	setTopic(const std::string & str);

		/* Booleans */

		bool	checkChannelName(const std::string &str) const;

		bool	isInChannel(AClient*const client) const;
		bool	isInChannel(const std::string& clientNickname) const;

		bool	isVisibleForClient(AClient*const client) const;

		bool	isOperator(AClient const* client) const;						// also check for Creators
		bool	isOperator(const std::string& clientNickname) const;	// also check for Creators

		bool	isCreator(AClient const* client) const;
		bool	isCreator(const std::string& clientNickname) const;

		bool	isStatusVoice(AClient const* user) const;
		bool	isStatusBanned(AClient const* user) const;
		bool	isStatusException(AClient const* user) const;
		bool	isStatusInvite(AClient const* user) const;

		bool	isLocalChannel(void) const;
		bool	isNetworkChannel(void) const;
		bool	isNetworkSafeChannel(void) const;
		bool	isNetworkUnmoderatedChannel(void) const;

		bool	isLocalChannelVisibleForClient(AClient const* client) const;

		/* Message / Notice */

		void	receiveMessage(AClient*const client, std::string const &message);
		void	receiveNotice(AClient *const client, std::string const &message);

		/* Modifiers */

		bool	addClient(AClient*const client, std::string& password, bool isChannelOperator = false);
		//bool	addServer(__Server*const server);

		bool	removeClient(AClient*const client, std::string const &leaveMessage);

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

#include <irc/replies/CommandReplies.hpp>
#include <irc/replies/ErrorReplies.hpp>

namespace irc
{
	///////////////////////////
	// ChannelClient members //
	///////////////////////////

	inline
	ChannelClient::
	ChannelClient()
	{ }

	inline
	ChannelClient::
	ChannelClient(AClient* const client, bool isOp)
	: client(client)
	{ static_cast<void>(isOp); }

	inline
	ChannelClient::
	ChannelClient(AClient* const client)
	: client(client)
	{ }

	inline
	ChannelClient::
	ChannelClient(const ChannelClient& src)
	{ *this = src; }

	inline
	ChannelClient::
	~ChannelClient()
	{ }

	inline
	ChannelClient&
	ChannelClient::
	operator=(const ChannelClient& src)
	{
		client = src.client;
		return (*this);
	}

	/////////////////////
	// Channel members //
	/////////////////////

	inline
	Channel::
	~Channel()
	{ }

	/* template <class __Server, class AClient>
	Channel const&
	Channel::
	operator<<(PrivateMessage const& reply)
	{
		for (Channel::channelClientMap::iterator it = clientsMap.begin() ; it != clientsMap.end() ; it++)
			*it->first << reply;
		return (*this);
	} */

	/////////////
	// Getters //
	/////////////

	inline const std::string&
	Channel::
	getTopic() const
	{ return (topic); }

	/////////////
	// Setters //
	/////////////

	inline void
	Channel::
	setTopic(const std::string& str)
	{ topic = str; }
	//////////////
	// Booleans //
	//////////////

	inline bool
	Channel::
	isInChannel(AClient*const client) const
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

	inline bool
	Channel::
	isOperator(AClient const* client) const
	{ return (check_user_mod(channelModes.channelModes, client->nickname, Channel::O | Channel::o)); }

	inline bool
	Channel::
	isCreator(AClient const* client) const
	{ return (check_user_mod(channelModes.channelModes, client->nickname, Channel::O)); }

	inline bool
	Channel::
	isStatusVoice(AClient const* user) const
	{ return (check_user_mod(channelModes.channelModes, user->nickname, Channel::v)); }

	inline bool
	Channel::
	isStatusBanned(AClient const* user) const
	{ return (check_user_mod(channelModes.channelModes, user->nickname, Channel::b)); }

	inline bool
	Channel::
	isStatusException(AClient const* user) const
	{ return (check_user_mod(channelModes.channelModes, user->nickname, Channel::e)); }

	inline bool
	Channel::
	isStatusInvite(AClient const* user) const
	{ return (check_user_mod(channelModes.channelModes, user->nickname, Channel::i)); }

	inline bool
	Channel::
	isLocalChannelVisibleForClient(AClient const* client) const
	{ return (!isLocalChannel() || client->isLocal()); }

	inline bool
	Channel::
	isVisibleForClient(AClient*const client) const
	{ return (isInChannel(client) || (!(channelModes & (Channel::p | Channel::s))
	&& isLocalChannelVisibleForClient(client))); }

	inline bool
	Channel::
	isOperator(const std::string& clientNickname) const
	{ return (check_user_mod(channelModes.channelModes, clientNickname, Channel::O | Channel::o)); }

	inline bool
	Channel::
	isCreator(const std::string& clientNickname) const
	{ return (check_user_mod(channelModes.channelModes, clientNickname, Channel::O)); }

	inline bool
	Channel::
	isLocalChannel(void) const
	{ return (channelType == '&'); }

	inline bool
	Channel::
	isNetworkChannel(void) const
	{ return (channelType == '#'); }

	inline bool
	Channel::
	isNetworkSafeChannel(void) const
	{ return (channelType == '!'); }

	inline bool
	Channel::
	isNetworkUnmoderatedChannel(void) const
	{ return (channelType == '+'); }

	//////////////////////
	// Message / Notice //
	//////////////////////

	inline bool
	Channel::
	close()
	{
		// FIXME
/*
		if (!serversMap.empty())
			serversMap.begin()->second->database.channels.erase(name); */
		// delete this;
		// I don't think we can delete ourselves
		return (true);
	}

	/////////////////
	// Handle mods //
	/////////////////

	namespace
	{
		template <class __Reply, class Channel>
		inline bool
		user_in_channel(const std::string& nickname, Channel* const c)
		{
			if (!c->isInChannel(nickname))
			{
				__Reply(gHostname, nickname, c->name);
				return (false);
			}
			return (true);
		}

		template <class __Reply, class Map, class Channel>
		bool
		add_mode(Map& m, Channel* const c, const std::string& key, size_t mask,
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

		template <class __Reply, class Map, class Channel>
		bool
		reset_mode(Map& m, Channel* const c, const std::string& key, size_t mask,
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

	inline bool
	Channel::
	addCreator(const std::string& nickname)
	{
		return (user_in_channel<UserNotInChannelError>(nickname, this)
		&& add_mode<ChannelModeIsReply>(channelModes.channelModes, this, nickname, Channel::O, "+O"));
	}

	inline bool
	Channel::
	removeCreator(const std::string& nickname)
	{
		return (user_in_channel<UserNotInChannelError>(nickname, this)
		&& reset_mode<ChannelModeIsReply>(channelModes.channelModes, this, nickname, Channel::O, "-O"));
	}

	inline bool
	Channel::
	addOperator(const std::string& nickname)
	{
		return (user_in_channel<UserNotInChannelError>(nickname, this)
		&& add_mode<ChannelModeIsReply>(channelModes.channelModes, this, nickname, Channel::o, "+o"));
	}

	inline bool
	Channel::
	removeOperator(const std::string& nickname)
	{
		return (user_in_channel<UserNotInChannelError>(nickname, this)
		&& reset_mode<ChannelModeIsReply>(channelModes.channelModes, this, nickname, Channel::o, "-o"));
	}

	inline bool
	Channel::
	addVoice(const std::string& nickname)
	{
		return (user_in_channel<UserNotInChannelError>(nickname, this)
		&& add_mode<ChannelModeIsReply>(channelModes.channelModes, this, nickname, Channel::v, "+v"));
	}

	inline bool
	Channel::
	removeVoice(const std::string& nickname)
	{
		return (user_in_channel<UserNotInChannelError>(nickname, this)
		&& reset_mode<ChannelModeIsReply>(channelModes.channelModes, this, nickname, Channel::v, "-v"));
	}

	inline bool
	Channel::
	addBanned(const std::string& nickname)
	{ return (add_mode<BanListReply>(channelModes.channelModes, this, nickname, Channel::b, "+")); }

	inline bool
	Channel::
	removeBanned(const std::string& nickname)
	{ return (reset_mode<BanListReply>(channelModes.channelModes, this, nickname, Channel::b, "-")); }

	inline bool
	Channel::
	addException(const std::string& nickname)
	{ return (add_mode<ExceptionListReply>(channelModes.channelModes, this, nickname, Channel::e, "+")); }

	inline bool
	Channel::
	removeException(const std::string& nickname)
	{ return (reset_mode<ExceptionListReply>(channelModes.channelModes, this, nickname, Channel::e, "-")); }

	inline bool
	Channel::
	addInviteList(const std::string& nickname)
	{ return (add_mode<InviteListReply>(channelModes.channelModes, this, nickname, Channel::I, "+")); }

	inline bool
	Channel::
	removeInviteList(const std::string& nickname)
	{ return (reset_mode<InviteListReply>(channelModes.channelModes, this, nickname, Channel::I, "-")); }
}
