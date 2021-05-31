#include <irc/AClient.hpp>

#include <irc/Database.hpp>

#include <irc/commands/utils.hpp>

#include <utils/Logger.hpp>

namespace NAMESPACE_IRC
{

// --- Client ---

	// It is worth to redo Client class with templates to avoid
	// forward refereneces and define those 2 in hpp ??

	void
	AClient::joinChannel(Channel* const channel)
	{ channels.insert(channelPair(channel->name, channel)); }

	bool
	AClient::isInChannel(Channel* const channel) const
	{ return (channels.find(ft::strToLower(channel->name)) != channels.end()); }

	AClient::AClient(bool authRequired)
		:	ABufferedConnection(!authRequired),
			registered(false)
	{
		Logger::instance() << Logger::DEBUG << "Constructing Client..." << std::endl;
		//readBuffer.reserve(IRC_MESSAGE_MAXLEN);
	} // TODO: Maybe reserve writeBuffer

	void	AClient::leaveChannel(Channel* const channel)
	{
		if (channels.find(channel->name) == channels.end())
			return ;
		channels.erase(ft::strToLower(channel->name));
	}

	void	AClient::leaveChannel(std::string const& channelName)
	{
		channelMap::iterator it = channels.find(ft::strToLower(channelName));

		if (it == channels.end())
			return ;
		channels.erase(ft::strToLower(channelName));
	}

	void	AClient::leaveAllChannels()
	{
		channelMap::iterator it;

		while (!channels.empty())
		{
			it = channels.begin();
			it->second->removeClient(this, "");
		}
	}

	bool	AClient::isInSameChannel(AClient const* client) const
	{
		channelMap::const_iterator itb = channels.begin();
		channelMap::const_iterator ite = channels.end();
		while (itb != ite)
		{
			if (client->isInChannel(itb->first))
				return true;
			itb++;
		}
		return false;
	}

	void	AClient::welcome(Database const& db)
	{
		if (!registered && nickname != IRC_NICKNAME_DEFAULT
		&& !username.empty() && authenticated)
		{
			*this
			<< WelcomeReply(db.hostname, nickname, username, hostname)
			<< YourHostReply(db.hostname, SERVER_VERSION)
			<< CreatedReply(db.hostname, db.createdAt)
			<< MyInfoReply(db.hostname, SERVER_VERSION, MODES_CLIENT, MODES_CHANNEL);
			registered = true;
		}
	}

	/// Get a joined channel.
	Channel	*AClient::getChannel(std::string const & channelName) const
	{
		if (isInChannel(channelName))
			return channels.find(ft::strToLower(channelName))->second;
		return NULL;
	}

	bool	AClient::listChannelInfo(Channel* const channel)
	{
		if (!channel)
			return false;

		std::string const &channelName = channel->name;

		if (!isInChannel(channelName))
		{
			if (channel->channelModes & Channel::s)
				return false;
			else if (channel->channelModes & Channel::p)
			{
				*this << ListReply(gHostname, channelName, 0, "Prv");
				return false;
			}
			else if (channel->isLocalChannelVisibleForClient(this))
				*this << ListReply(gHostname, channelName, channel->clientsMap.size(), channel->topic);
			return false; // TODO: Check if this should return true, or bool anyways
		}
		else
			*this << ListReply(gHostname, channelName, channel->clientsMap.size(), channel->topic);
		return true;
	}

	bool	AClient::listAllChannelsListInfo(Database const& db)
	{
		for (Database::channelMap::const_iterator it = db.dataChannelsMap.begin();
			it != db.dataChannelsMap.end(); it++)
			this->listChannelInfo(it->second);
		return true;
	}

		bool	AClient::listChannelWhoQueryInfo(Channel* const channel, int opFlag)
	{
		if (!channel)
			return false;

		std::string const &channelName = channel->name;

		if (!isInChannel(channelName) &&
			((channel->channelModes & Channel::s) || (channel->channelModes & Channel::p)))
				return false;
		else
		{
			Channel::channelClientMap::iterator itb = channel->clientsMap.begin();
			Channel::channelClientMap::iterator ite = channel->clientsMap.end();
			while (itb != ite)
			{
				if (!opFlag || channel->isOperator(itb->first))
					*this << WhoReply(gHostname, channelName, itb->first, channel->isOperator(itb->first));
				itb++;
			}
		}
		return true;
	}

	bool	AClient::listAllVisibleUsersWhoQueryInfo(Database const& db)
	{
		for (Database::clientMap::const_iterator it = db.dataClientsMap.begin();
			it != db.dataClientsMap.end(); it++)
		{
			AClient*	client = it->second;
			if (!client->modes[i] && !this->isInSameChannel(client))
				*this << WhoReply(gHostname, "", client, -1);
		}
		return true;
	}

	bool	AClient::matchMaskWhoQueryInfo(Database const& db, std::string const &mask)
	{
		// currently match with users' host, real name and nickname
		// to do :
		//		match with users' server
		for (Database::clientMap::const_iterator it = db.dataClientsMap.begin();
			it != db.dataClientsMap.end(); it++)
		{
			AClient*	client = it->second;
			if (!client->modes[i] &&
					(matchPattern_global(client->nickname, mask) ||
					matchPattern_global(client->username, mask) ||
					matchPattern_global(client->hostname, mask)))
				*this << WhoReply(gHostname, "", client, -1);
		}
		return true;
	}
}
