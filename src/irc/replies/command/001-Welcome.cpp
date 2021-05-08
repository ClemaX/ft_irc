#include <irc/replies/CommandReplies.hpp>

namespace irc
{
// 001     IRC_RPL_WELCOME
//             "Welcome to the Internet Relay Network <nick>!<user>@<host>"
	WelcomeReply::WelcomeReply(const std::string& serverName, const std::string& nickname,
	const std::string& username, const std::string& hostname)
	: NumericReply(serverName, IRC_RPL_WELCOME) // Change by define
	{ std::cout << "Welcome to the Internet Relay Network " << nickname << "!" << username << "@"
	<< hostname << std::endl; }
}
