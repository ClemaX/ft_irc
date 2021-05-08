#include <irc/replies/NumericReplies.hpp>
#include <irc/replies/CommandReplies.hpp>
#include <irc/Client.hpp>
#include <irc/Channel.hpp>

namespace irc
{

// 001     IRC_RPL_WELCOME
//             "Welcome to the Internet Relay Network <nick>!<user>@<host>"
	WelcomeReply::WelcomeReply(const std::string& serverName, const std::string& nickname,
	const std::string& username, const std::string& hostname)
	: NumericReply(serverName, IRC_RPL_WELCOME)
	{ message << "Welcome to the Internet Relay Network " << nickname << "!" << username << "@"
	<< hostname; }

// 002     IRC_RPL_YOURHOST
//             "Your host is <servername>, running version <ver>"
	YourHostReply::YourHostReply(const std::string& serverName, const std::string& versionName)
	: NumericReply(serverName, IRC_RPL_YOURHOST)
	{ message << "Your host is" << serverName << ", running version " << versionName; }

// 003     IRC_RPL_CREATED
//             "This server was created <date>"
	CreatedReply::CreatedReply(const std::string& serverName, const std::string& date)
	: NumericReply(serverName, IRC_RPL_CREATED)
	{ message << "This server was created " << date; }

// 004     IRC_RPL_MYINFO
//             "<servername> <version> <available user modes> <available channel modes>"
	MyInfoReply::MyInfoReply(const std::string& serverName, const std::string& version,
	const std::string& umodes, const std::string& chmodes)
	: NumericReply(serverName, IRC_RPL_MYINFO)
	{ message << serverName << " " << version << " " << umodes << " " << chmodes; }

// 005     IRC_RPL_BOUNCE
//             "Try server <server name>, port <port number>"
	BounceReply::BounceReply(const std::string& serverName, const std::string& portNB)
	: NumericReply(serverName, IRC_RPL_BOUNCE)
	{ std::cout << "Try server " << serverName << ", port " << portNB << std::endl; }

// 302     IRC_RPL_USERHOST
//             ":[<reply>{<space><reply>}]"
	UserhostReply::UserhostReply(std::string const& serverName, clientList users)
		: NumericReply(serverName, IRC_RPL_USERHOST)
	{
		for (clientList::const_iterator it = users.begin(); it != users.end(); ++it)
		{
			std::cout << (*it)->nickname;
		}
	}

// 303     IRC_RPL_ISON
//             ":[<nick> {<space><nick>}]"

// 301     IRC_RPL_AWAY
//             "<nick> :<away message>"
	AwayReply::AwayReply(std::string const& serverName, std::string const &nickName,
							std::string const &awayMessage)
		: NumericReply(serverName, IRC_RPL_AWAY)
	{
		message << nickName << " :" << awayMessage;
	}

// 305     IRC_RPL_UNAWAY
//             ":You are no longer marked as being away"
// 306     IRC_RPL_NOWAWAY
//             ":You have been marked as being away"

// 311     IRC_RPL_WHOISUSER
//             "<nick> <user> <host> * :<real name>"
// 312     IRC_RPL_WHOISSERVER
//             "<nick> <server> :<server info>"
// 313     IRC_RPL_WHOISOPERATOR
//             "<nick> :is an IRC operator"
// 317     IRC_RPL_WHOISIDLE
//             "<nick> <integer> :seconds idle"
// 318     IRC_RPL_ENDOFWHOIS
//             "<nick> :End of /WHOIS list"
// 319     IRC_RPL_WHOISCHANNELS
//             "<nick> :{[@|+]<channel><space>}"

// 314     IRC_RPL_WHOWASUSER
//             "<nick> <user> <host> * :<real name>"
// 369     IRC_RPL_ENDOFWHOWAS
//             "<nick> :End of WHOWAS"

// 321     IRC_RPL_LISTSTART
//             "Channel :Users Name"
// 322     IRC_RPL_LIST
//             "<channel> <# visible> :<topic>"
	ListReply::ListReply(std::string const& serverName, std::string const &channelName,
							int numberOfUsers, std::string const &topic)
		: NumericReply(serverName, IRC_RPL_LIST)
	{
		message << channelName;
		if (numberOfUsers)
			message << " " << ft::itoa(numberOfUsers);
		if (topic.compare(""))
			message << " " << topic;
	}
// 323     IRC_RPL_LISTEND
//             ":End of /LIST"
	EndOfListReply::EndOfListReply(std::string const& serverName)
		: NumericReply(serverName, IRC_RPL_LISTEND)
	{
		message << ":End of /LIST";
	}

// 325     IRC_RPL_UNIQOPIS
//             "<channel> <nickname>"
	UniqOpIsReply::UniqOpIsReply(std::string const& serverName, std::string const &channelName,
							std::string const &nickName)
		: NumericReply(serverName, IRC_RPL_UNIQOPIS)
	{
		message << channelName << " " << nickName;
	}

// 324     IRC_RPL_CHANNELMODEIS
//             "<channel> <mode> <mode params>"
	ChannelModeIsReply::ChannelModeIsReply(std::string const& serverName, std::string const &channelName,
							std::string const &mode, std::string const &modeParams)
		: NumericReply(serverName, IRC_RPL_CHANNELMODEIS)
	{
		message << channelName << " " << mode;
		if (!modeParams.compare(""))
			message << " " << modeParams;
	}

// 331     IRC_RPL_NOTOPIC
//             "<channel> :No topic is set"
	NoTopicReply::NoTopicReply(std::string const& serverName, std::string const &channelName)
		: NumericReply(serverName, IRC_RPL_NOTOPIC)
	{
		message << channelName << " :No topic is set";
	}
// 332     IRC_RPL_TOPIC
//             "<channel> :<topic>"
	TopicReply::TopicReply(std::string const& serverName, std::string const &channelName,
							std::string const &topic)
		: NumericReply(serverName, IRC_RPL_TOPIC)
	{
		message << channelName << " :" << topic;
	}

// 341     IRC_RPL_INVITING
//             "<channel> <nick>"
	InvitingReply::InvitingReply(std::string const& serverName, std::string const &channelName,
							std::string const &nickname)
		: NumericReply(serverName, IRC_RPL_INVITING)
	{
		message << nickname << " has been invited to join " << channelName;
	}

// 342     IRC_RPL_SUMMONING
//             "<user> :Summoning user to IRC"

// 346 IRC_RPL_INVITELIST
//             "<channel> <invitemask>"
	InviteListReply::InviteListReply(std::string const& serverName, std::string const &channelName,
							std::string const &sign, std::string const &inviteMask)
		: NumericReply(serverName, IRC_RPL_INVITELIST)
	{
		message << channelName << " " << sign << "I " << inviteMask;
	}
// 347 IRC_RPL_ENDOFINVITELIST
//             "<channel> :End of channel invite list"
	EndOfInviteListReply::EndOfInviteListReply(std::string const& serverName, std::string const &channelName)
		: NumericReply(serverName, IRC_RPL_ENDOFINVITELIST)
	{
		message << channelName << " :End of channel invite list";
	}
// 348 IRC_RPL_EXCEPTLIST
//             "<channel> <exceptionmask>"
	ExceptionListReply::ExceptionListReply(std::string const& serverName, std::string const &channelName,
							std::string const &sign, std::string const &exceptionMask)
		: NumericReply(serverName, IRC_RPL_EXCEPTLIST)
	{
		message << channelName << " " << sign << "e " << exceptionMask;
	}
// 349 IRC_RPL_ENDOFEXCEPTLIST
//             "<channel> :End of channel exception list"
	EndOfExceptionListReply::EndOfExceptionListReply(std::string const& serverName, std::string const &channelName)
		: NumericReply(serverName, IRC_RPL_ENDOFEXCEPTLIST)
	{
		message << channelName << " :End of channel exception list";
	}
// 351     IRC_RPL_VERSION
//             "<version>.<debuglevel> <server> :<comments>"

// 352     IRC_RPL_WHOREPLY
//             "<channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real name>"
	WhoReply::WhoReply(std::string const& serverName, std::string const &mask, Client *client, int op)	// need to add host, server, hopcount
		: NumericReply(serverName, IRC_RPL_WHOREPLY)
	{
		message << mask << " " << serverName << " " << client->nickname;
		if (op == 1)
			message << " @";
		else if (!op)
			message << " +";
		message << " " << client->username;


	}
// 315     IRC_RPL_ENDOFWHO
//             "<name> :End of /WHO list"
	EndOfWhoReply::EndOfWhoReply(std::string const& serverName, std::string const &mask)
		: NumericReply(serverName, IRC_RPL_ENDOFWHO)
	{
		message << mask << " :End of /WHO list";
	}

// 353     IRC_RPL_NAMREPLY
//             "<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]"
	ChannelNamesReply::ChannelNamesReply(std::string const& serverName, Channel *channel)
		: NumericReply(serverName, IRC_RPL_NAMREPLY)
	{
		message << channel->name << " :";
		for (Channel::channelClientMap::const_iterator it = channel->clientsMap.begin(); it != channel->clientsMap.end(); it++)
		{
			if (channel->isOperator(it->first))
				message << "@";
			else
				message << "+";		// need to be checked
			message << it->first->nickname << " ";
		}
	}
// 366     IRC_RPL_ENDOFNAMES
//             "<channel> :End of /NAMES list"
	EndOfNamesReply::EndOfNamesReply(std::string const& serverName, std::string const &channelName)
		: NumericReply(serverName, IRC_RPL_ENDOFNAMES)
	{
		message << channelName << " :End of /NAMES list";
	}
// 364     IRC_RPL_LINKS
//             "<mask> <server> :<hopcount> <server info>"
// 365     IRC_RPL_ENDOFLINKS
//             "<mask> :End of /LINKS list"

// 367     IRC_RPL_BANLIST
//             "<channel> <banid>"
	BanListReply::BanListReply(std::string const& serverName, std::string const &channelName,
							std::string const &sign, std::string const &banid)
		: NumericReply(serverName, IRC_RPL_BANLIST)
	{
		message << channelName << " " << sign << "b " << banid;
	}
// 368     IRC_RPL_ENDOFBANLIST
//             "<channel> :End of channel ban list"
	EndOfBanListReply::EndOfBanListReply(std::string const& serverName, std::string const &channelName)
		: NumericReply(serverName, IRC_RPL_ENDOFBANLIST)
	{
		message << channelName << " :End of channel ban list";
	}

// 371     IRC_RPL_INFO
//             ":<string>"
// 374     IRC_RPL_ENDOFINFO
//             ":End of /INFO list"

// 375     IRC_RPL_MOTDSTART
//             ":- <server> Message of the day - "
MotdStartReply::MotdStartReply(std::string const& serverName, std::string const& nickName, std::string const& motd)
		throw(InvalidMessageException)
		: NumericReply(serverName, IRC_RPL_MOTDSTART, nickName)
	{
		if (motd.length() > 80)
			throw (InvalidMessageException()); // TODO: Maybe use another (Reply-)exception type

		if (message.length())
			message.push_back(IRC_MESSAGE_DELIM);
		message << ":- " << serverName << " " << motd << " -";
	}

// 372     IRC_RPL_MOTD
//             ":- <text>"
	MotdReply::MotdReply(std::string const& serverName,
		std::string const& nickName, std::string const& motd)
		throw(InvalidMessageException)
		: NumericReply(serverName, IRC_RPL_MOTD, nickName)
	{
		if (motd.length() > 80)
			throw (InvalidMessageException()); // TODO: Maybe use another (Reply-)exception type
		if (message.length())
			message.push_back(IRC_MESSAGE_DELIM);
		message << ":- " << motd << " -";
	}

// 376     IRC_RPL_ENDOFMOTD
//             ":End of /MOTD command"
	EndOfMotdReply::EndOfMotdReply(std::string const& serverName,
		std::string const& nickName)
		: NumericReply(serverName, IRC_RPL_ENDOFMOTD, nickName)
	{
		if (message.length())
			message.push_back(IRC_MESSAGE_DELIM);
		message << ":End of /MOTD command.";
	}

// 381     IRC_RPL_YOUREOPER
//             ":You are now an IRC operator"

// 382     IRC_RPL_REHASHING
//             "<config file> :Rehashing"

// 391     IRC_RPL_TIME
//             "<server> :<string showing server's local time>"

// 392     IRC_RPL_USERSSTART
//             ":UserID Terminal Host"
// 393     IRC_RPL_USERS
//             ":%-8s %-9s %-8s"
// 394     IRC_RPL_ENDOFUSERS
//             ":End of users"
// 395     IRC_RPL_NOUSERS
//             ":Nobody logged in"

// 200     IRC_RPL_TRACELINK
//             "Link <version & debug level> <destination> <next server>"
// 201     IRC_RPL_TRACECONNECTING
//             "Try. <class> <server>"
// 202     IRC_RPL_TRACEHANDSHAKE
//             "H.S. <class> <server>"
// 203     IRC_RPL_TRACEUNKNOWN
//             "???? <class> [<client IP address in dot form>]"
// 204     IRC_RPL_TRACEOPERATOR
//             "Oper <class> <nick>"
// 205     IRC_RPL_TRACEUSER
//             "User <class> <nick>"
// 206     IRC_RPL_TRACESERVER
//             "Serv <class> <int>S <int>C <server> <nick!user|!>@<host|server>"
// 208     IRC_RPL_TRACENEWTYPE
//             "<newtype> 0 <client name>"
// 261     IRC_RPL_TRACELOG
//             "File <logfile> <debug level>"

// 211     IRC_RPL_STATSLINKINFO
//             "<linkname> <sendq> <sent messages> <sent bytes> <received messages> <received bytes> <time open>"
// 212     IRC_RPL_STATSCOMMANDS
//             "<command> <count>"
// 213     IRC_RPL_STATSCLINE
//             "C <host> * <name> <port> <class>"
// 214     IRC_RPL_STATSNLINE
//             "N <host> * <name> <port> <class>"
// 215     IRC_RPL_STATSILINE
//             "I <host> * <host> <port> <class>"
// 216     IRC_RPL_STATSKLINE
//             "K <host> * <username> <port> <class>"
// 218     IRC_RPL_STATSYLINE
//             "Y <class> <ping frequency> <connect frequency> <max sendq>"
// 219     IRC_RPL_ENDOFSTATS
//             "<stats letter> :End of /STATS report"
// 241     IRC_RPL_STATSLLINE
//             "L <hostmask> * <servername> <maxdepth>"
// 242     IRC_RPL_STATSUPTIME
//             ":Server Up %d days %d:%02d:%02d"
// 243     IRC_RPL_STATSOLINE
//             "O <hostmask> * <name>"
// 244     IRC_RPL_STATSHLINE
//             "H <hostmask> * <servername>"

// 221     IRC_RPL_UMODEIS
//             "<user mode string>"
	UModeIsReply::UModeIsReply(std::string const& serverName, std::string const &userMode)
		: NumericReply(serverName, IRC_RPL_UMODEIS)
	{
		message << userMode;
	}

// 251     IRC_RPL_LUSERCLIENT
//             ":There are <integer> users and <integer> invisible on <integer> servers"
// 252     IRC_RPL_LUSEROP
//             "<integer> :operator(s) online"
// 253     IRC_RPL_LUSERUNKNOWN
//             "<integer> :unknown connection(s)"
// 254     IRC_RPL_LUSERCHANNELS
//             "<integer> :channels formed"
// 255     IRC_RPL_LUSERME
//             ":I have <integer> clients and <integer> servers"

// 256     IRC_RPL_ADMINME
//             "<server> :Administrative info"
// 257     IRC_RPL_ADMINLOC1
//             ":<admin info>"
// 258     IRC_RPL_ADMINLOC2
//             ":<admin info>"
// 259     IRC_RPL_ADMINEMAIL
//             ":<admin info>"

// 263    IRC_RPL_TRYAGAIN
//             "<command> :Please wait a while and try again."

	NickReplyNoNickGiven::NickReplyNoNickGiven(const std::string& servername)
	: NumericReply(servername, ERR_NONICKNAMEGIVEN, ":No nickname given")
	{ }

	NickReplyInvFormat::NickReplyInvFormat(const std::string& servername,
	const std::string& given_nick)
	: NumericReply(servername, ERR_ERRONEUSNICKNAME, given_nick + " :Erroneous nickname")
	{ }

	NickReplyAlreadyInUse::NickReplyAlreadyInUse(const std::string& servername,
	const std::string& given_nick)
	: NumericReply(servername, ERR_NICKNAMEINUSE, given_nick + " :Nickname is already in use")
	{ }

	NickReplyRegisterCollision::NickReplyRegisterCollision(const std::string& servername,
	const std::string& given_nick, const std::string& username, const std::string& hostname)
	: NumericReply(servername, ERR_NICKCOLLISION, given_nick + " :Nickname collision KILL from "
	+ username + "@" + hostname)
	{ }
}
