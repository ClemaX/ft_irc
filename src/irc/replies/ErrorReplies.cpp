#include <irc/replies/NumericReplies.hpp>
#include <irc/replies/ErrorReplies.hpp>
#include <irc/Client.hpp>

namespace irc
{

// 401     IRC_ERR_NOSUCHNICK
//             "<nickname> :No such nick/channel"

// 402     IRC_ERR_NOSUCHSERVER
//             "<server name> :No such server"

// 403     IRC_ERR_NOSUCHCHANNEL
//             "<channel name> :No such channel"
	NoSuchChannelError::NoSuchChannelError(std::string const& serverName,
		std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_NOSUCHCHANNEL)
	{
		message.append(channelName).append(" :No such channel");
	}
// 404     IRC_ERR_CANNOTSENDTOCHAN
//             "<channel name> :Cannot send to channel"

// 405     IRC_ERR_TOOMANYCHANNELS
//             "<channel name> :You have joined too many channels"
	TooManyChannelsError::TooManyChannelsError(std::string const& serverName,
		std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_TOOMANYCHANNELS)
	{
		message.append(channelName).append(" :You have joined too many channels");
	}
// 406     IRC_ERR_WASNOSUCHNICK
//             "<nickname> :There was no such nickname"

// 407     IRC_ERR_TOOMANYTARGETS
//             "<target> :Duplicate recipients. No message"
	TooManyTargetError::TooManyTargetError(std::string const& serverName,
		std::string const& TargetName)
		:	NumericReply(serverName, IRC_ERR_TOOMANYTARGETS)
	{
		message.append(TargetName).append(" :Duplicate recipients. No message");
	}
// 409     IRC_ERR_NOORIGIN
//             ":No origin specified"

// 411     IRC_ERR_NORECIPIENT
//             ":No recipient given (<command>)"

// 412     IRC_ERR_NOTEXTTOSEND
//             ":No text to send"

// 413     IRC_ERR_NOTOPLEVEL
//             "<mask> :No toplevel domain specified"

// 414     IRC_ERR_WILDTOPLEVEL
//             "<mask> :Wildcard in toplevel domain"

// 421     IRC_ERR_UNKNOWNCOMMAND
//             "<command> :Unknown command"

// 422     IRC_ERR_NOMOTD
//             ":MOTD File is missing"

// 423     IRC_ERR_NOADMININFO
//             "<server> :No administrative info available"

// 424     IRC_ERR_FILEERROR
//             ":File error doing <file op> on <file>"

// 431     IRC_ERR_NONICKNAMEGIVEN
//             ":No nickname given"

// 432     IRC_ERR_ERRONEUSNICKNAME
//             "<nick> :Erroneus nickname"

// 433     IRC_ERR_NICKNAMEINUSE
//             "<nick> :Nickname is already in use"

// 436     IRC_ERR_NICKCOLLISION
//             "<nick> :Nickname collision KILL"

// 437     IRC_ERR_UNAVAILRESOURCE
//             "<nick/channel> :Nick/channel is temporarily unavailable"
	UnavailableResourceError::UnavailableResourceError(std::string const& serverName,  std::string const &nickname,
			std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_UNAVAILRESOURCE)
	{
		message.append(nickname).append("/").append(channelName).append(" :Nick/channel is temporarily unavailable");
	}

// 441     IRC_ERR_USERNOTINCHANNEL
//             "<nick> <channel> :They aren't on that channel"

// 442     IRC_ERR_NOTONCHANNEL
//             "<channel> :You're not on that channel"

// 443     IRC_ERR_USERONCHANNEL
//             "<user> <channel> :is already on channel"

// 444     IRC_ERR_NOLOGIN
//             "<user> :User not logged in"

// 445     IRC_ERR_SUMMONDISABLED
//             ":SUMMON has been disabled"

// 446     IRC_ERR_USERSDISABLED
//             ":USERS has been disabled"

// 451     IRC_ERR_NOTREGISTERED
//             ":You have not registered"

// 461     IRC_ERR_NEEDMOREPARAMS
//             "<command> :Not enough parameters"
	NeedMoreParamsError::NeedMoreParamsError(std::string const& serverName,
		std::string const& commandName)
		:	NumericReply(serverName, IRC_ERR_NEEDMOREPARAMS)
	{
		message.append(commandName).append(" :Not enough parameters");
	}

// 462     IRC_ERR_ALREADYREGISTRED
//             ":You may not reregister"

// 463     IRC_ERR_NOPERMFORHOST
//             ":Your host isn't among the privileged"

// 464     IRC_ERR_PASSWDMISMATCH
//             ":Password incorrect"

// 465     IRC_ERR_YOUREBANNEDCREEP
//             ":You are banned from this server"

// 467     IRC_ERR_KEYSET
//             "<channel> :Channel key already set"

// 471     IRC_ERR_CHANNELISFULL
//             "<channel> :Cannot join channel (+l)"
	ChannelIsFullError::ChannelIsFullError(std::string const& serverName,
		std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_CHANNELISFULL)
	{
		message.append(channelName).append(" :Cannot join channel (+l)");
	}

// 472     IRC_ERR_UNKNOWNMODE
//             "<char> :is unknown mode char to me"

// 473     IRC_ERR_INVITEONLYCHAN
//             "<channel> :Cannot join channel (+i)"
	InviteOnlyChanError::InviteOnlyChanError(std::string const& serverName,
		std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_INVITEONLYCHAN)
	{
		message.append(channelName).append(" :Cannot join channel (+i)");
	}

// 474     IRC_ERR_BANNEDFROMCHAN
//             "<channel> :Cannot join channel (+b)"
	BannedFromChanError::BannedFromChanError(std::string const& serverName,
		std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_BANNEDFROMCHAN)
	{
		message.append(channelName).append(" :Cannot join channel (+b)");
	}

// 475     IRC_ERR_BADCHANNELKEY
//             "<channel> :Cannot join channel (+k)"
	BadChannelKeyError::BadChannelKeyError(std::string const& serverName,
		std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_BADCHANNELKEY)
	{
		message.append(channelName).append(" :Cannot join channel (+k)");
	}
// 476		IRC_ERR_BADCHANMASK
//             	"<channel> :Bad Channel Mask"
	BadChanMaskError::BadChanMaskError(std::string const& serverName,
		std::string const& channelName)
		:	NumericReply(serverName, IRC_ERR_BADCHANMASK)
	{
		message.append(channelName).append(" :Bad Channel Mask");
	}
// 477		IRC_ERR_NOCHANMODES
//             	"<channel> :Channel doesn't support modes"
// 478		IRC_ERR_BANLISTFULL
//             	"<channel> <char> :Channel list is full"

// 481     IRC_ERR_NOPRIVILEGES
//             ":Permission Denied- You're not an IRC operator"

// 482     IRC_ERR_CHANOPRIVSNEEDED
//             "<channel> :You're not channel operator"

// 483     IRC_ERR_CANTKILLSERVER
//             ":You cant kill a server!"

// 491     IRC_ERR_NOOPERHOST
//             ":No O-lines for your host"

// 501     IRC_ERR_UMODEUNKNOWNFLAG
//             ":Unknown MODE flag"

// 502     IRC_ERR_USERSDONTMATCH
//             ":Cant change mode for other users"


}
