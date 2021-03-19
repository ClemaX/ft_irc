#pragma once

/// IRC default TLS/SSL TCP-port (as defined in RFC7194).
#define IRC_PORT_SSL 6697U
/// Maximal length of IRC client nicknames (as defined in RFC1459 1.2).
#define IRC_NICKNAME_MAXLEN 9U
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
#define IRC_MESSAGE_SUFFIX "\r\n"
/// Maximal length of IRC messages (as defined in RFC1459 2.3).
#define IRC_MESSAGE_MAXLEN 512
