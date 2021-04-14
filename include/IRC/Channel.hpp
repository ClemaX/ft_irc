#pragma once

#include <map> // using std::map
#include <set> // using std::set

#include <iostream> // using std::cout // for testing for now

#include <irc/Client.hpp>
#include <irc/Server.hpp>
#include <utils/strings.hpp>

namespace irc
{

	class Server;
	class Client;
	// TODO: Reference to connection and add ChannelClient on JOIN command
	struct	ChannelClient
	{
		Client*	client;
		// bool	isChannelOperator;	// not used, the operators are stored in the channelNicknameMap channel->channelModes.o

		ChannelClient();
		ChannelClient(Client* client);
		ChannelClient(Client* client, bool isOp);
		ChannelClient(const ChannelClient & src);

		~ChannelClient();

		ChannelClient & operator=(const ChannelClient & src);
	};

	struct	ChannelModes
	{
	private:
			// typedef std::map<Client*, ChannelClient> channelClientMap;
			typedef std::map<Server*, Server*> channelServerMap;
			typedef std::map<std::string, std::string> channelNicknameMap;

	public:
		channelNicknameMap	O;
		channelNicknameMap	o;
		channelNicknameMap	v;

		bool	a;
		bool	i;
		bool	m;
		bool	n;
		bool	q;
		bool	p;
		bool	s;
		bool	r;
		bool	t;

		size_t	l;
		std::string	k;

		channelNicknameMap	b;
		channelNicknameMap	e;
		channelNicknameMap	I;

		// O - give "channel creator" status;
    	// o - give/take channel operator privilege;
    	// v - give/take the voice privilege;

		// a - toggle the anonymous channel flag;
    	// i - toggle the invite-only channel flag;
    	// m - toggle the moderated channel;
    	// n - toggle the no messages to channel from clients on the outside;
  		// q - toggle the quiet channel flag;
    	// p - toggle the private channel flag;
    	// s - toggle the secret channel flag;
 		// r - toggle the server reop channel flag;
    	// t - toggle the topic settable by channel operator only flag;

    	// k - set/remove the channel key (password);
    	// l - set/remove the user limit to channel;

    	// b - set/remove ban mask to keep users out;
 		// e - set/remove an exception mask to override a ban mask;
 		// I - set/remove an invitation mask to automatically override the invite-only flag;

		ChannelModes();
		~ChannelModes();

	};

	class	Channel
	{


	public:
		typedef std::map<Client*, ChannelClient> channelClientMap;
		typedef std::map<Server*, Server*> channelServerMap;
		typedef std::map<std::string, std::string> channelNicknameMap;
		// typedef std::pair<Client*, ChannelClient> channelClientPair;
		// typedef std::pair<Server*, Server*> channelServerPair;

		class	ChannelException		:	public std::exception { };

		class	InvalidChannelNameException	:	public ChannelException
		{
			public: char const*	what() const throw()
			{ return "Invalid channel name"; };
		};

	private:
		Channel();

	public:
		channelClientMap	clientsMap;
		channelServerMap	serversMap;
		std::string			topic;

		ChannelModes		channelModes;
		std::string const			name;

		Channel(std::string const& channelName) throw(InvalidChannelNameException);
		~Channel();

		Channel const&	operator<<(NumericReply const& reply);

	// Get functions
		// ChannelModes	getModes() const;
		std::string	getTopic() const;
		Client *getUser(std::string const & clientNickname) const;

	// Set functions
		void	setTopic(const std::string & str);

	// Check functions
		bool	checkChannelName(const std::string &str) const;

		bool	isInChannel(Client *client) const;
		bool	isInChannel(std::string const & clientNickname) const;

		bool	isVisible(Client *client) const;

		bool	isOperator(Client *client) const;						// also check for Creators
		bool	isOperator(std::string const & clientNickname) const;	// also check for Creators

		bool	isCreator(Client *client) const;
		bool	isCreator(std::string const & clientNickname) const;

		bool	isStatusBanned(Client *user) const;
		bool	isStatusException(Client *user) const;
		bool	isStatusInvite(Client *user) const;


	// Add/Remove functions
		bool	addClient(Server const& server, Client* client, std::string& password, bool isChannelOperator = false);
		bool	addServer(Server* server);

		bool	removeClient(Client* client);

		bool	close();

	// Modes functions

		bool	addCreator(std::string nickname);
		bool	removeCreator(std::string nickname);

		bool	addOperator(std::string nickname);
		bool	removeOperator(std::string nickname);

		bool	addVoice(std::string nickname);
		bool	removeVoice(std::string nickname);


		bool	addBanned(std::string nickname);
		bool	removeBanned(std::string nickname);

		bool	addException(std::string nickname);
		bool	removeException(std::string nickname);

		bool	addInviteList(std::string nickname);
		bool	removeInviteList(std::string nickname);

	};
}
