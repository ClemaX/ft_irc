#include <irc/Database.hpp>

namespace irc
{
	Database&
	Database::
	operator=(const Database& other)
	{
		if (this != &other)
		{
			dataServersMap = other.dataServersMap;
			dataChannelsMap = other.dataChannelsMap;
			dataClientsMap = other.dataClientsMap;
			modeChannelFunctionsMap = other.modeChannelFunctionsMap;
			modeUserFunctionsMap = other.modeUserFunctionsMap;
		}
		return (*this);
	}

	void
	Database::
	createModeFunctionsMap()
	{
		modeChannelFunctionsMap['+'] = getPlusChannelMap();
		modeChannelFunctionsMap['-'] = getMinusChannelMap();
		modeUserFunctionsMap['+'] = getPlusUserMap();
		modeUserFunctionsMap['-'] = getMinusUserMap();
	}

	bool	Database::parseUserMode(AClient *user, std::string & flags,
		std::string & flagArguments)
	{
		char sign = flags[0];
		std::string userMode = "";
		userMode.push_back(sign);
		if (sign != '+' && sign != '-')
		{
			*user << UModeUnkownFlagError(gHostname);
			return false;
		}

		flags.erase(0, 1);
		for (std::string::iterator it = flags.begin(); it != flags.end(); it++)
		{
			if (modeUserFunctionsMap[sign].find(*it) == modeUserFunctionsMap[sign].end())
				*user << UModeUnkownFlagError(gHostname);
			else
			{
				modeUserFunctionsMap[sign][*it](user, NULL, flagArguments);
				userMode.replace(1, 1, 1, *it);
				*user << UModeIsReply(gHostname, userMode);
			}
		}
		return true;
	}

	bool	Database::parseChannelMode(AClient *user, std::string const & channelName,
			std::string & flags, std::string & flagArguments)
	{
		Channel *channel = user->getChannel(channelName);

		if (!channel)
			channel = getChannel(channelName);

		if (!channel || !channel->isVisibleForClient(user))
		{
			*user << NoSuchChannelError(gHostname, channelName);
			return false;
		}

		if (channel->isNetworkUnmoderatedChannel())
		{
			*user << NoChanModesError(gHostname, channelName);
			return false;
		}

		char sign = flags[0];
		if (sign != '+' && sign != '-')
		{
			*user << UModeUnkownFlagError(gHostname);
			return false;
		}

		flags.erase(0, 1);
		for (std::string::iterator it = flags.begin(); it != flags.end(); it++)
		{
			if (modeChannelFunctionsMap[sign].find(*it) == modeChannelFunctionsMap[sign].end())
				return false;
			modeChannelFunctionsMap[sign][*it](user, channel, flagArguments);
		}
		return true;
	}

}
