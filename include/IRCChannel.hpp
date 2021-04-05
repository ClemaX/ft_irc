#pragma once

#include <map> // using std::map
#include <set> // using std::set

#include <iostream> // using std::cout // for testing for now

#include <IRCClient.hpp>
#include <IRCServer.hpp>

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
		channelNicknameMap	o;
		bool	p;
		bool	s;
		bool	i;
		bool	t;
		bool	n;
		bool	m;
		size_t	l;
		channelNicknameMap	b;
		channelNicknameMap	v;
		std::string	k;

		// o - give/take channel operator privileges;
        // p - private channel flag;
        // s - secret channel flag;
        // i - invite-only channel flag;
        // t - topic settable by channel operator only flag;
        // n - no messages to channel from clients on the outside;
        // m - moderated channel;
        // l - set the user limit to channel;
        // b - set a ban mask to keep users out;
        // v - give/take the ability to speak on a moderated channel;
        // k - set a channel key (password).

		ChannelModes();
		~ChannelModes();

	};

	class	Channel
	{
	protected:
		typedef std::map<Client*, ChannelClient> channelClientMap;
		typedef std::map<Server*, Server*> channelServerMap;
		typedef std::map<std::string, std::string> channelNicknameMap;
		// typedef std::pair<Client*, ChannelClient> channelClientPair;
		// typedef std::pair<Server*, Server*> channelServerPair;


	public:
		channelClientMap	clientsMap;
		channelServerMap	serversMap;
		std::string			topic;
		
		ChannelModes		channelModes;
		std::string const			name;

		Channel();
		Channel(std::string const& name);
		~Channel();

		// ChannelModes	getModes() const;
		std::string	getTopic() const;

		void	setTopic(const std::string & str);

		bool	isInChannel(Client *client) const;
		bool	isInChannel(std::string const & clientNickname) const;
		bool	isOperator(Client *client) const;
		bool	isOperator(std::string const & clientNickname) const;

		Client *getUser(std::string const & clientNickname) const;

		void	displayNicknames(void) const;

		bool	addClient(Client* client, bool	isChannelOperator = false);
		bool	addServer(Server* server);

		bool	removeClient(Client* client);

		bool	close();

		// Modes functions	// left to code

		bool	addOperator(std::string nickname);
		bool	removeOperator(std::string nickname);
		
		bool	addBanned(std::string nickname);
		bool	removeBanned(std::string nickname);
		
		bool	addVoice(std::string nickname);
		bool	removeVoice(std::string nickname);
	};
}
