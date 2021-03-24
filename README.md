
This file contains the RFC documentation summary.

# 1. RFC 1459:

## 1.1 Servers
User can connect to a server.
Servers can connect to other servers.
Servers structure is an extended binary tree ( https://www.geeksforgeeks.org/extended-binary-tree/ ).
	- Where each server is the central node (for the chunk of the network that each server can "see").

## 1.2 Clients
A client is anything that is connected to a server (exept a server).
Each client is distinguished to other clients using an unique nickname (9 bytes max lenght).
Also all the servers need to have the following information about all the clients:
	- the real name of the host that the client is connected.
	- the username of the client of that host.
	- the server that the client is connected.

### 1.2.1 Operators
Operators are admins.
SQUIT (4.1.7).
CONNECT (4.3.5).
KILL (4.6.1).

## 1.3 Chanels
A channel is a named group containing > 1 clients which recives the channel msgs.
The channel is implicitly created when the first client joins it.
The channel is implicitly destroyed when the last client lefts it.
Until the channel exists any client can refer to this channel using its name.
Chanels names :
	- Are strings.
	- Begin with '&' or '#'.
	- 200 bytes max sized.
	- Can't contain whitespaces.
	- Can't contain ctrl^G (ASCII 7).
	- Can't contain a ','.
2 kinds of channels can exist:
	- Chanels distributed all over the network (all the servers) -> '#'.
	- Local server channel -> '&'.
MODE (4.2.3).
To create a new channel or join an existing one, a user must use "JOIN" command.
The first client to join a channel becomes the operator of the channel.
Else if the channel already exist: check 8.13.
If the connection between 2 servers breaks up, for a channel which clients are in both servers, when the connection is restored both servers will anounce to each other all the JOINs and MODEs of the channel.

### 1.3.1 Chanel operator
The channel operator owns the channel.
It can cast some commands:
	- KICK: kick out of the channel a user.
	- MODE: change channel modes.
	- INVITE: invite a user to the channel.
	- TOPIC: Change the channel topic (requires +t mode).
Using commands "NAMES", "WHO" or "WHOIS" the operator nickname starts with a '@'.

## 2.2 Chars
Unique bytes are used to send mgs (char, uchar, int8_t, uint8_t, ...).
Some bytes values are however used as messages delimitors:
	- '{', '}', '|' are lowercases.
	- '[', ']', '\' are uppercases.

## 2.3 Messages
Servers and clients send to each other messages and those messages can generate or not an answer.
If a user cast a valid command, the server behaviour should be as specified in the documentation.
The comunication between client & server is essentally asyncronous.
Each IRC message can consist on (separeted with at least 1 space):
	- <optional> prefix:
		- start ':' (0x3b) and be followed by the prefix (no spaces between).
		- is used by severs to indicate the origin of the msg
			(no prefix == msg comes from same connection as the msg receptor).
		- Client shouldn't use prefixes for sending msgs, if they do the only valid prefix
			is the nickname associated with the client.
		- If the prefix isn't in the database or the prefix or the sender does not match with
			the msg prefix the server must ignore the msg (in a silent way).
	- command: must be an IRC valid command or 3 digits representing ASCII text.
	- parameters: max == 15.
Each message is finished by CR (0x0d) - LF (0x0a).
A message max lenght is 512 - CR-LF = 510.
More details in section 7.

### 2.3.1 Messages format in pseudocode
<message>		-> [':' <prefix> <space> ] <command> <parram> <CR-LF>
<prefix>		-> <server name> | <nick> ['!' <user> ] ['@' <host> ]
<command>		-> <char> { <char> } | <digit> <digit> <digit>
<space>		-> ' ' { ' ' } (0x20)
<param>			-> <space> [':' <final param> | <middle param> <final param> ]
<final param>	-> any kind of bytes sequence (empty too) exept <CR-LF> or 0x0
<middle param>	-> any kind of bytes seqence (not empty) exept <CR-LF> or 0x0
<CR-LF>			-> 0x0d - 0x0a

\<message\>		-\> [':' \<prefix\> \<space\> ] \<command\> \<parram\> \<CR-LF\> \n
\<prefix\>		-\> \<server name\> | \<nick\> ['!' \<user\> ] ['@' \<host\> ] \n
\<command\>		-\> \<char\> { \<char\> } | \<digit\> \<digit\> \<digit\> \n
\<space\>		-\> ' ' { ' ' } (0x20) \n
\<param\>			-\> \<space\> [':' \<final param\> | \<middle param\> \<final param\> ] \n
\<final param\>	-\> any kind of bytes sequence (empty too) exept \<CR-LF\> or 0x0 \n
\<middle param\>	-\> any kind of bytes seqence (not empty) exept \<CR-LF\> or 0x0 
\<CR-LF\>			-> 0x0d - 0x0a	\n

#### Notes:
1) <space> is only 0x20 not whitespaces.
2) <final param> and <middle param> are only used to accept spaces in a param
	(just a syntactical trick).
3) CR and LF can't be part of the msg (logical).
4) 0x0 can't be used inside a msg for C/C++ reasons.
5) The last <param> must be an empty string.
6) The prefix "['!' <user> ] ['@' <host> ]" must not be used in
	server - server comunication, its only server - client oriented.

<target>		-> <a> <"," <target>
<a>				-> <channel> | <user> '@' <server name> | <nick> | <mask>
<channel>		-> ('#' | '&') <string>
<server name>	-> <host>
<host>			-> see RFC 952 [DNS:4]
<mask>			-> ('#' |'&') <string>
<string>		-> any 1bytes value exept: space, bell, cr, lf, coma.

<user> 			-> <string with coma> { <string with coma> }
<leter>			-> 'a' ... 'z' | 'A' ... 'Z'
<digit>			-> '0' ... '9'
<especial>		-> '-' | '[' | ']' | '\' \ '`' | '^' | '{' '}'

## 2.4 Numeric answers
The most common answer (for error and not error).
Composed by:
	- 1) The sender prefix.
	- 2) 3 digit integer.
	- 3) The receiver.
A client can't raise a numeric answer (it's silently ignored).
Section 6 contains the numeric answers codes list.

## 3.1 One to one comunication
Usualy one to one comunication is only done by clients.
To ensure a secure way of comunication between clients it's necessary that all the servers are able to send a msg in a precise direction (to any client).
The shortest path wins.

### 3.2.1 One to list comunication
Worts groupal method (send message N times for N members in the list).

### 3.2.2 One to a group (channel) comunication
The conversation is only sent to servers used by the users of the channel.
If there are more than 1 user in the same server and in the same channel, the	message is sent once to the server.

### 3.2.3 One to host/server mask comunication
Same as previous.

### 3.3.1 Client to client comunication
There's any kind of unique message that can be sent to all the clients.

### 3.3.2 Client to server comunication
Commands change the state of a channel, a user ...
Must be sent to all the servers all over the network.

### 3.3.3 Server to server comunication
Almost every msg sent server to server is distributed all over the network to all servers.





