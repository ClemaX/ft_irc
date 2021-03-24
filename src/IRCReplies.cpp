#include <IRCReplies.hpp>
#include <IRCClient.hpp>

namespace irc
{
	NumericReply::NumericReply(std::string const& serverName,
		int code, std::string const& message = "")
		:	prefix(serverName),
			code(code),
			message(message)
	{ }

	NumericReply::~NumericReply()
	{ }

	std::string	NumericReply::serialize() const throw()
	{
		std::string	serialized;

		serialized.append(prefix.serialize());
		serialized.push_back(IRC_MESSAGE_DELIM);
		serialized.append(ft::itoa(code));
		serialized.push_back(IRC_MESSAGE_DELIM);
		serialized.append(message);
		serialized.append(IRC_MESSAGE_SUFFIX);

		return serialized;
	}

	NeedMoreParamsReply::NeedMoreParamsReply(std::string const& serverName,
		std::string const& commandName)
		:	NumericReply(serverName, IRC_ERR_NEEDMOREPARAMS)
	{
		message.append(commandName).append(": Not enough parameters");
	}

	UserhostReply::UserhostReply(std::string const& serverName, clientList users)
		: NumericReply(serverName, IRC_RPL_USERHOST)
	{
		for (clientList::const_iterator it = users.begin(); it != users.end(); ++it)
		{
			std::cout << (*it)->nickname;
		}
	}

}
