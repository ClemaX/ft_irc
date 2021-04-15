#pragma once

// #include <irc/replies/NumericReplies.hpp>

namespace irc
{
	struct	NumericReply;
	class	Client;
	class	Channel;
	struct	AMessage;

	typedef	std::vector<Client const*> clientList;

// 001     IRC_RPL_WELCOME
//             "Welcome to the Internet Relay Network <nick>!<user>@<host>"
// 002     IRC_RPL_YOURHOST
//             "Your host is <servername>, running version <ver>"
// 003     IRC_RPL_CREATED
//             "This server was created <date>"
// 004     IRC_RPL_MYINFO
//             "<servername> <version> <available user modes> <available channel modes>"
// 005     IRC_RPL_BOUNCE
//             "Try server <server name>, port <port number>"

// 302     IRC_RPL_USERHOST
//             ":[<reply>{<space><reply>}]"
	struct UserhostReply	:	NumericReply
	{ UserhostReply(std::string const& serverName, clientList users); };

// 303     IRC_RPL_ISON
//             ":[<nick> {<space><nick>}]"

// 301     IRC_RPL_AWAY
//             "<nick> :<away message>"
	struct AwayReply	:	NumericReply
	{ AwayReply(std::string const& serverName, std::string const &nickName,
		std::string const& awayMessage); };

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
	struct ListReply	:	NumericReply
	{ ListReply(std::string const& serverName, std::string const &channelName,
							int numberOfUsers, std::string const &topic); };
// 323     IRC_RPL_LISTEND
//             ":End of /LIST"
	struct EndOfListReply	:	NumericReply
	{ EndOfListReply(std::string const& serverName); };

// 325     IRC_RPL_UNIQOPIS
//             "<channel> <nickname>"
	struct UniqOpIsReply	:	NumericReply
	{ UniqOpIsReply(std::string const& serverName, std::string const &channelName,
							std::string const &nickName); };

// 324     IRC_RPL_CHANNELMODEIS
//             "<channel> <mode> <mode params>"
	struct ChannelModeIsReply	:	NumericReply
	{ ChannelModeIsReply(std::string const& serverName, std::string const &channelName,
							std::string const &mode, std::string const &modeParams); };

// 331     IRC_RPL_NOTOPIC
//             "<channel> :No topic is set"
	struct NoTopicReply	:	NumericReply
	{ NoTopicReply(std::string const& serverName, std::string const &channelName); };

// 332     IRC_RPL_TOPIC
//             "<channel> :<topic>"
	struct TopicReply	:	NumericReply
	{ TopicReply(std::string const& serverName, std::string const &channelName,
							std::string const &topic); };

// 341     IRC_RPL_INVITING
//             "<channel> <nick>"
	struct InvitingReply	:	NumericReply
	{ InvitingReply(std::string const& serverName, std::string const &channelName,
							std::string const &nickname); };

// 342     IRC_RPL_SUMMONING
//             "<user> :Summoning user to IRC"

// 346 IRC_RPL_INVITELIST
//             "<channel> <invitemask>"
	struct InviteListReply	:	NumericReply
	{ InviteListReply(std::string const& serverName, std::string const &channelName,
							std::string const &sign, std::string const &inviteMask); };
// 347 IRC_RPL_ENDOFINVITELIST
//             "<channel> :End of channel invite list"
	struct EndOfInviteListReply	:	NumericReply
	{ EndOfInviteListReply(std::string const& serverName, std::string const &channelName); };
// 348 IRC_RPL_EXCEPTLIST
//             "<channel> <exceptionmask>"
	struct ExceptionListReply	:	NumericReply
	{ ExceptionListReply(std::string const& serverName, std::string const &channelName,
							std::string const &sign, std::string const &exceptionMask); };
// 349 IRC_RPL_ENDOFEXCEPTLIST
//             "<channel> :End of channel exception list"
	struct EndOfExceptionListReply	:	NumericReply
	{ EndOfExceptionListReply(std::string const& serverName, std::string const &channelName); };

// 351     IRC_RPL_VERSION
//             "<version>.<debuglevel> <server> :<comments>"

// 352     IRC_RPL_WHOREPLY
//             "<channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real name>"
// 315     IRC_RPL_ENDOFWHO
//             "<name> :End of /WHO list"

// 353     IRC_RPL_NAMREPLY
//             "<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]"
	struct ChannelNamesReply	:	NumericReply
	{ ChannelNamesReply(std::string const& serverName, Channel *channel); };
// 366     IRC_RPL_ENDOFNAMES
//             "<channel> :End of /NAMES list"
	struct EndOfNamesReply	:	NumericReply
	{ EndOfNamesReply(std::string const& serverName, std::string const &channelName); };

// 364     IRC_RPL_LINKS
//             "<mask> <server> :<hopcount> <server info>"
// 365     IRC_RPL_ENDOFLINKS
//             "<mask> :End of /LINKS list"

// 367     IRC_RPL_BANLIST
//             "<channel> <banid>"
	struct BanListReply	:	NumericReply
	{ BanListReply(std::string const& serverName, std::string const &channelName,
							std::string const &sign, std::string const &banid); };
// 368     IRC_RPL_ENDOFBANLIST
//             "<channel> :End of channel ban list"
	struct EndOfBanListReply	:	NumericReply
	{ EndOfBanListReply(std::string const& serverName, std::string const &channelName); };

// 371     IRC_RPL_INFO
//             ":<string>"
// 374     IRC_RPL_ENDOFINFO
//             ":End of /INFO list"

// 375     IRC_RPL_MOTDSTART
//             ":- <server> Message of the day - "
	struct MotdStartReply	:	NumericReply
	{
		MotdStartReply(std::string const& serverName,
			std::string const& nickName, std::string const& motd)
			throw(AMessage::InvalidMessageException);
	};
// 372     IRC_RPL_MOTD
//             ":- <text>"
	struct MotdReply		:	NumericReply
	{
		MotdReply(std::string const& serverName, std::string const& nickName,
			std::string const& motd)
			throw(AMessage::InvalidMessageException);
	};	
// 376     IRC_RPL_ENDOFMOTD
//             ":End of /MOTD command"
	struct EndOfMotdReply	:	NumericReply
	{
		EndOfMotdReply(std::string const& serverName,
			std::string const& nickName);
	};
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
	struct UModeIsReply	:	NumericReply
	{ UModeIsReply(std::string const& serverName, std::string const &userMode); };

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

}
