#include <irc/Replies.hpp>
#include <irc/Client.hpp>

namespace irc
{
	NeedMoreParamsReply::NeedMoreParamsReply(std::string const& serverName,
		std::string const& commandName)
		:	NumericReply(serverName, IRC_ERR_NEEDMOREPARAMS)
	{
		message.append(commandName).append(": Not enough parameters");
	}

	
}
