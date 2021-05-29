#include <irc/replies/CommandReplies.hpp>

#include <irc/AClient.hpp>

namespace NAMESPACE_IRC
{
// 302     IRC_RPL_USERHOST
//             ":[<reply>{<space><reply>}]"
	UserhostReply::UserhostReply(std::string const& serverName, clientList users)
		: NumericReply(serverName, IRC_RPL_USERHOST)
	{
		for (clientList::const_iterator it = users.begin(); it != users.end(); ++it)
		{
			//TODO: std::cout << (*it)->nickname;
		}
	}
}
