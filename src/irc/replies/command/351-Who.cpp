#include <irc/replies/CommandReplies.hpp>
#include <irc/AClient.hpp>

namespace NAMESPACE_IRC
{
// 352     IRC_RPL_WHOREPLY
//             "<channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real name>"
	WhoReply::WhoReply(std::string const& serverName, std::string const &mask, AClient *client, int op)	// need to add host, server, hopcount
		: NumericReply(serverName, IRC_RPL_WHOREPLY)
	{
		if (!mask.empty())
			message += mask + " ";

		message += serverName + " " + client->nickname;
		if (op == 0)
			message += " +";
		else if (op == 1)
			message += " @";

		message += " " + client->username;
	}
}
