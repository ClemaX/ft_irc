#include <irc/Channel.hpp>

namespace irc
{
	Channel::
	Channel(std::string const& channelName)
	throw(InvalidChannelNameException)
	: name(setChannelName(channelName))
	{
		if (checkChannelName(name) == false)
			throw InvalidChannelNameException();
		else if (isNetworkUnmoderatedChannel())
			channelModes = Channel::m | Channel::t;
	}

	bool
	Channel::
	checkChannelName(const std::string& str) const
	{
		return (!((str.length() < 2UL || str.length() > 50UL)
		|| (str.at(0) != '&' && str.at(0) != '#' && str.at(0) != '+' && str.at(0) != '!')
		|| (str.find(' ') != std::string::npos || str.find(',') != std::string::npos || str.find('\'') != std::string::npos)));
	}

	std::string
	Channel::
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
}
