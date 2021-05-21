#pragma once

/// irc namespace
#define NAMESPACE_IRC irc

/// Current version of the irc server
#define SERVER_VERSION "2.0.0" // corrected 1 time

/// Creation date of the irc server
#define SERVER_CREATION_DATE "the 20 april of 2021"

/// Get the array @p x size
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*x))

/// Avalaible user modes
#define MODES_CLIENT "iswo"
/// Avalaibe channel modes
#define MODES_CHANNEL "OovaimnqpsrtklbeI"
/// Special IRC characters allowed outside of the alphanumerical set.
#define IRC_CHARSET_SPECIAL    "-[]\\`^{}"

/// Define default server admin nickname
#define IRC_DFT_ADMIN_NICK "admin"
/// Define default server admin password
#define IRC_DFT_ADMIN_PASS "admin"
/// Define default server admin data1
#define IRC_DFT_ADMIN_DATA1 ":You're using ircserv! For assistance, please '/stats p' and message someone on the list"
/// Define defualt server admin data2
#define IRC_DFT_ADMIN_DATA2 ":For further assistance, please contact us by email"
/// Define default server admin email
#define IRC_DFT_ADMIN_EMAIL "admin@ircserv.42fr"

/// IRC default TLS/SSL TCP-port (as defined in RFC7194).
#define IRC_PORT_SSL 6697U
/// Maximal length of IRC client nicknames (as defined in RFC1459 1.2).
#define IRC_NICKNAME_MAXLEN 9U
/// Default IRC client nickname to be assigned on connection.
#define IRC_NICKNAME_DEFAULT "*"
/// Maximal length of IRC channel names (as defined in RFC1459 1.3).
#define IRC_CHANNEL_NAME_MAXLEN 200U
/// Allowed prefix characters for IRC channel names (as defined in RFC1459 1.3).
#define IRC_CHANNEL_NAME_PREFIX_WHITELIST "&#"
#define IRC_CHANNEL_NAME_PREFIX_DISTRIB '&'
/// Banned characters for IRC channel names (as defined in RFC1459 1.3).
#define IRC_CHANNEL_NAME_BLACKLIST " \a,"
/// Nickname prefix for IRC channel operator. (used in channel-bound commands, as defined in RFC1459 1.3.1)
#define IRC_CHANNEL_OP_PREFIX '@'
/// IRC message field-delimiter (as defined in RFC1459 2.3)
#define IRC_MESSAGE_DELIM ' '
/// IRC message-prefix indicator-prefix (as defined in RFC1459 2.3)
#define IRC_MESSAGE_PREFIX_PREFIX ':'
/// IRC message-prefix user-indicator-prefix (as defined in RFC1459 2.3.1)
#define IRC_MESSAGE_PREFIX_USER_PREFIX '!'
/// IRC message-prefix host-indicator-prefix (as defined in RFC1459 2.3.1)
#define IRC_MESSAGE_PREFIX_HOST_PREFIX '@'
/// IRC message suffix. (as defined in RFC1459 2.3)
#define IRC_MESSAGE_SUFFIX "\r\n"				// How can we get the '\r' ?
/// Maximal length of IRC messages (as defined in RFC1459 2.3).
#define IRC_MESSAGE_MAXLEN 512

/// IRC message field-delimiter (as defined in RFC1459 2.3)
#define IRC_MESSAGE_ARGUMENT_LIST_DELIM ','

// Maximal number of channels that a user can join
#define IRC_MAX_JOINED_CHANNEL 10


// ===== Errors ===== //

/// Used to indicate the nickname parameter supplied to a command is currently unused.
#define IRC_ERR_NOSUCHNICK 401
/// Used to indicate the server name given currently doesn't exist.
#define IRC_ERR_NOSUCHSERVER 402
/// Used to indicate the given channel name is invalid.
#define IRC_ERR_NOSUCHCHANNEL 403
/// Sent to a user who is not allowed to send a message to a channel.
#define IRC_ERR_CANNOTSENDTOCHAN 404
/// Sent to a user when they have joined the maximum number of allowed channels and try to join another.
#define IRC_ERR_TOOMANYCHANNELS 405
/// Returned by WHOWAS to indicate there is no history information for that nickname.
#define IRC_ERR_WASNOSUCHNICK 406
/// Returned to a client which is attempting to send a PRIVMSG/NOTICE using the user@host destination format and for a user@host which has several occurrences.
#define IRC_ERR_TOOMANYTARGETS 407
/// PING or PONG message missing the originator parameter which is required since these commands must work without valid prefixes.
#define IRC_ERR_NOORIGIN 409
/// The command is missing a recipient parameter.
#define IRC_ERR_NORECIPIENT 411
/// Used to indicate that there is no text to send.
#define IRC_ERR_NOTEXTTOSEND 412
/// Used to indicate a missing toplevel domain parameter.
#define IRC_ERR_NOTOPLEVEL 413
/// Used to indicate a wildcard in a toplevel domain parameter.
#define IRC_ERR_WILDTOPLEVEL 414
/// Returned to a registered client to indicate that the command sent is unknown by the server.
#define IRC_ERR_BADMASK 415
#define IRC_ERR_TOOMANYMATCHES 416

#define IRC_ERR_UNKNOWNCOMMAND 421
/// Server's MOTD file could not be opened by the server.
#define IRC_ERR_NOMOTD 422
/// Returned by a server in response to an ADMIN message when there is an error in finding the appropriate information.
#define IRC_ERR_NOADMININFO 423
/// Generic error message used to report a failed file operation during the processing of a message.
#define IRC_ERR_FILEERROR 424
/// Returned when a nickname parameter expected for a command and isn't found.
#define IRC_ERR_NONICKNAMEGIVEN 431
/// Returned after receiving a NICK message which contains invalid characters.
#define IRC_ERR_ERRONEUSNICKNAME 432
/// Returned when a NICK message is processed that results in an attempt to change to a currently existing nickname.
#define IRC_ERR_NICKNAMEINUSE 433
/// Returned by a server to a client when it detects a nickname collision (registered of a NICK that already exists by another server).
#define IRC_ERR_NICKCOLLISION 436
/// Returned by the server to indicate that the target user of the command is not on the given channel.
#define IRC_ERR_UNAVAILRESOURCE 437
/// Returned by the server to indicate that the target user of the command is not on the given channel.
#define IRC_ERR_USERNOTINCHANNEL 441
/// Returned by the server whenever a client tries to perform a channel effecting command for which the client isn't a member.
#define IRC_ERR_NOTONCHANNEL 442
/// Returned when a client tries to invite a user to a channel they are already on.
#define IRC_ERR_USERONCHANNEL 443
/// Returned by the summon after a SUMMON command for a user was unable to be performed since they were not logged in.
#define IRC_ERR_NOLOGIN 444
/// Returned as a response to an unimplemented SUMMON command.
#define IRC_ERR_SUMMONDISABLED 445
/// Returned as a response to an unimplemented USERS command.
#define IRC_ERR_USERSDISABLED 446
/// Returned by the server to indicate that the client must be registered before the server will allow it to be parsed in detail.
#define IRC_ERR_NOTREGISTERED 451
/// Returned by the server by numerous commands to indicate to the client that it didn't supply enough parameters.
#define IRC_ERR_NEEDMOREPARAMS 461
/// Returned by the server to any link which tries to change part of the registered details (such as password or user details from second USER message).
#define IRC_ERR_ALREADYREGISTRED 462
/// Returned to a client which attempts to register with a server which does not been setup to allow connections from the host the attempted connection is tried.
#define IRC_ERR_NOPERMFORHOST 463
/// Returned to indicate a failed attempt at registering a connection for which a password was required and was either not given or incorrect.
#define IRC_ERR_PASSWDMISMATCH 464
/// Returned after an attempt to connect and register yourself with a server which has been setup to explicitly deny connections to you.
#define IRC_ERR_YOUREBANNEDCREEP 465
/// Returned after an attempt to set a key on channel where there is already a key set.
#define IRC_ERR_KEYSET 467
/// Returned after an attempt to join a channel that is already full.
#define IRC_ERR_CHANNELISFULL 471
/// Used to indicate an unknown mode.
#define IRC_ERR_UNKNOWNMODE 472
/// Returned after an attempt to join an invite-only channel without having been invited.
#define IRC_ERR_INVITEONLYCHAN 473
/// Returned after an attempt to join a channel after having been banned.
#define IRC_ERR_BANNEDFROMCHAN 474
/// Returned after an attempt to join a channel using an invalid key.
#define IRC_ERR_BADCHANNELKEY 475
/// Any command requiring operator privileges to operate must return this error to indicate the attempt was unsuccessful.
#define IRC_ERR_BADCHANMASK 476
/// Any command requiring operator privileges to operate must return this error to indicate the attempt was unsuccessful.
#define IRC_ERR_NOCHANMODES 477
///
#define IRC_ERR_BANLISTFULL 478
///
#define IRC_ERR_NOPRIVILEGES 481
/// Any command requiring 'chanop' privileges (such as MODE messages) must return this error if the client making the attempt is not a chanop on the specified channel.
#define IRC_ERR_CHANOPRIVSNEEDED 482
/// Any attempts to use the KILL command on a serve are to be refused and this error returned directl to the client.
#define IRC_ERR_CANTKILLSERVER 483
/// If a client sends an OPER message and the server has not been configured to allow connections from the client's host as an operator, this error must be returned.
#define IRC_ERR_NOOPERHOST 491
/// Returned by the server to indicate that a MODE message was sent with a nickname parameter and that the a mode flag sent was not recognized.
#define IRC_ERR_UMODEUNKNOWNFLAG 501
/// Error sent to any user trying to view or change the user mode for a user other than themselves.
#define IRC_ERR_USERSDONTMATCH 502


// ===== Replies ===== //

/// Dummy reply number. Not used.
#define IRC_RPL_NONE 300
/// USERHOST command reply number.
#define IRC_RPL_USERHOST 302
/// ISON command reply number.
#define IRC_RPL_ISON 303
/// AWAY command reply number.
#define IRC_RPL_AWAY 301
/// UNAWAY command reply number.
#define IRC_RPL_UNAWAY 305
/// NOWAWAY command reply number.
#define IRC_RPL_NOWAWAY 306
/// WHOIS command reply number used to indicate an user.
#define IRC_RPL_WHOISUSER 311
/// WHOIS command reply number used to indicate a server.
#define IRC_RPL_WHOISSERVER 312
/// WHOIS command reply number used to indicate an operator.
#define IRC_RPL_WHOISOPERATOR 313
/// WHOIS command reply number used to indicate an idle user.
#define IRC_RPL_WHOISIDLE 317
/// WHOIS command reply number used to indicate the end of the reply.
#define IRC_RPL_ENDOFWHOIS 318
/// WHOIS command reply number used to indicate channels.
#define IRC_RPL_WHOISCHANNELS 319
/// WHOWAS command reply number used to indicate an user.
#define IRC_RPL_WHOWASUSER 314
/// WHOWAS command reply number used to indicate the end of the reply.
#define IRC_RPL_ENDOFWHOWAS 314
/// LIST command reply number used to indicate the start of the reply.
#define IRC_RPL_LISTSTART 321
/// LIST command reply number used to indicate the ccontent of the reply.
#define IRC_RPL_LIST 322
/// LIST command reply number used to indicate the end of the reply.
#define IRC_RPL_LISTEND 323
/// Numeric reply used to indicate the channel mode.
#define IRC_RPL_UNIQOPIS 325
#define IRC_RPL_CHANNELMODEIS 324
/// TOPIC command reply number used to indicate the absence of a topic.
#define IRC_RPL_NOTOPIC 331
/// TOPIC command reply number used to indicate the presence of a topic.
#define IRC_RPL_TOPIC 332
/// INVITE command reply number used to indicate a successful invitation.
#define IRC_RPL_INVITING 341
/// SUMMON command reply number used to indicate a successful summoning.
#define IRC_RPL_SUMMONING 342
/// Reply by the server using its version details.
#define IRC_RPL_INVITELIST 346
#define IRC_RPL_ENDOFINVITELIST 347
// When listing the 'invitations masks' for a given channel, a server is required to send the list back using the RPL_INVITELIST and RPL_ENDOFINVITELIST messages.  A separate RPL_INVITELIST is sent for each active mask. After the masks have been listed (or if none present) a RPL_ENDOFINVITELIST MUST be sent.
#define IRC_RPL_EXCEPTLIST 348
#define IRC_RPL_ENDOFEXCEPTLIST 349
// When listing the 'exception masks' for a given channel, a server is required to send the list back using the RPL_EXCEPTLIST and RPL_ENDOFEXCEPTLIST messages.  A separate RPL_EXCEPTLIST is sent for each active mask. After the masks have been listed (or if none present) a RPL_ENDOFEXCEPTLIST MUST be sent.
#define IRC_RPL_VERSION 351
/// WHO command reply number used to indicate a match.
#define IRC_RPL_WHOREPLY 352
/// WHO command reply number used to indicate the end of the reply.
#define IRC_RPL_ENDOFWHO 315
/// NAME command reply number used to indicate the content of the list.
#define IRC_RPL_NAMREPLY 353
/// NAME command reply number used to indicate the end of the list.
#define IRC_RPL_ENDOFNAMES 366
/// LINKS command reply number used to indicate the content of the list.
#define IRC_RPL_LINKS 364
/// LINKS command reply number used to indicate the end of the list.
#define IRC_RPL_ENDOFLINKS 365
/// BANLIST command reply number used to indicate the content of the list.
#define IRC_RPL_BANLIST 367
/// BANLIST command reply number used to indicate the end of the list.
#define IRC_RPL_ENDOFBANLIST 368
/// INFO command reply number used to indicate the content of the list.
#define IRC_RPL_INFO 371
/// INFO command reply number used to indicate the end of the list.
#define IRC_RPL_ENDOFINFO 374
/// MOTD command reply number used to indicate the start of the MOTD.
#define IRC_RPL_MOTDSTART 375
/// MOTD command reply number used to indicate the content of the MOTD.
#define IRC_RPL_MOTD 372
/// MOTD command reply number used to indicate the end of the MOTD.
#define IRC_RPL_ENDOFMOTD 376
/// OPER command reply number used to indicate success.
#define IRC_RPL_YOUREOPER 381
/// REHASH command reply number used to indicate success.
#define IRC_RPL_REHASHING 382
/// TIME command reply number.
#define IRC_RPL_TIME 391
/// USERS command reply number used to indicate the start of the list.
#define IRC_RPL_USERSTART 392
/// USERS command reply number used to indicate the content of the list.
#define IRC_RPL_USERS 393
/// USERS command reply number used to indicate the start of the list.
#define IRC_RPL_ENDOFUSERS 394
/// USERS command reply number used to indicate the absence of users.
#define IRC_RPL_NOUSERS 395

#define IRC_RPL_TRACELINK 200
#define IRC_RPL_TRACECONNECTING 201
#define IRC_RPL_TRACEHANDSHAKE 202
#define IRC_RPL_TRACEUNKNOWN 203
#define IRC_RPL_TRACEOPERATOR 204
#define IRC_RPL_TRACEUSER 205
#define IRC_RPL_TRACESERVER 206
#define IRC_RPL_TRACESERVICE 207
#define IRC_RPL_TRACENEWTYPE 208
#define IRC_RPL_TRACECLASS 209
#define IRC_RPL_TRACERECONNECT 210

#define IRC_RPL_TRACELOG 261
#define IRC_RPL_TRACEEND 262

#define IRC_RPL_STATSLINKINFO 211
#define IRC_RPL_STATSCOMMANDS 212

#define IRC_RPL_ENDOFSTATS 219

#define IRC_RPL_STATSUPTIME 242
#define IRC_RPL_STATSOLINE 243

#define IRC_RPL_UMODEIS 221

#define IRC_RPL_SERVLIST 234
#define IRC_RPL_SERVLISTEND 235

#define IRC_RPL_LUSERCLIENT 251
#define IRC_RPL_LUSEROP 252
#define IRC_RPL_LUSERUNKNOWN 253
#define IRC_RPL_LUSERCHANNELS 254
#define IRC_RPL_LUSERME 255
#define IRC_RPL_ADMINME 256
#define IRC_RPL_ADMINLOC1 257
#define IRC_RPL_ADMINLOC2 258
#define IRC_RPL_ADMINEMAIL 259

#define IRC_RPL_TRYAGAIN 263

#define IRC_RPL_WELCOME 1
#define IRC_RPL_YOURHOST 2
#define IRC_RPL_CREATED 3
#define IRC_RPL_MYINFO 4
#define IRC_RPL_BOUNCE 5

// NICK
#define ERR_NONICKNAMEGIVEN 431
#define ERR_ERRONEUSNICKNAME 432
#define ERR_NICKNAMEINUSE 433
#define ERR_NICKCOLLISION 436

// USER
#define ERR_NEEDMOREPARAMS 461
#define ERR_ALREADYREGISTRED 462

#define ERR_NOTREGISTRED 451




// TODO: Trace messages
// TODO: Stats messages
// TODO: Admin messages
