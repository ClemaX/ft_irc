#include <irc/Replies.hpp>
#include <irc/Client.hpp>

namespace irc
{
	UserhostReply::UserhostReply(std::string const& serverName, clientList users)
		: NumericReply(serverName, IRC_RPL_USERHOST)
	{
		for (clientList::const_iterator it = users.begin(); it != users.end(); ++it)
		{
			std::cout << (*it)->nickname;
		}
	}

	MotdStartReply::MotdStartReply(std::string const& serverName, std::string const& nickName, std::string const& motd)
		throw(InvalidMessageException)
		: NumericReply(serverName, IRC_RPL_MOTDSTART, nickName)
	{
		if (motd.length() > 80)
			throw (InvalidMessageException()); // TODO: Maybe use another (Reply-)exception type

		if (message.length())
			message.push_back(IRC_MESSAGE_DELIM);
		message.append(":- ").append(serverName).append(" ").append(motd)
			.append(" -");
	}

	MotdReply::MotdReply(std::string const& serverName,
		std::string const& nickName, std::string const& motd)
		throw(InvalidMessageException)
		: NumericReply(serverName, IRC_RPL_MOTD, nickName)
	{
		if (motd.length() > 80)
			throw (InvalidMessageException()); // TODO: Maybe use another (Reply-)exception type
		if (message.length())
			message.push_back(IRC_MESSAGE_DELIM);
		message.append(":- ").append(motd).append(" -");
	}

	EndOfMotdReply::EndOfMotdReply(std::string const& serverName,
		std::string const& nickName)
		: NumericReply(serverName, IRC_RPL_ENDOFMOTD, nickName)
	{
		if (message.length())
			message.push_back(IRC_MESSAGE_DELIM);
		message.append(":End of /MOTD command.");
	}

	
}
