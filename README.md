
This file contains the RFC documentation summary.  

# **RFC 1459:**
======

# SUMMARY

[1. Introduction](#1-introduction)  
* [1.1 Servers](#11-servers)  
* [1.2 Clients](#12-clients)  
* [1.3 Channels](#13-channels)  

[2. The IRC Specification](#2-the-irc-specification)  
* [2.2 Chars](#22-chars)  
* [2.3 Messages](#23-messages)  
* [2.4 Numeric answers](#24-numeric-answers)  

[3. IRC Concepts](#3-irc-concepts)  
* [3.1 One to one comunication](#31-one-to-one-comunication)  
* [3.2 One-to-many](#32-one-to-many)  
* [3.3 One-to-all](#33-one-to-all)  

[4. Message details](#4-message-details)  
* [4.1 Connection Registration](#41-connection-registration)  
* [4.2 Channel operations](#42-channel-operations)  
* [4.3 Server queries and commands](#43-server-queries-and-commands)  
* [4.4 Sending messages](#44-sending-messages)  

# 1. INTRODUCTION

## 1.1 Servers
User can connect to a server.  
Servers can connect to other servers.  
Servers structure is an extended binary tree ( https://www.geeksforgeeks.org/extended-binary-tree/ ).  
* Where each server is the central node (for the chunk of the network that each server can "see").  

## 1.2 Clients
A client is anything that is connected to a server (exept a server).  
Each client is distinguished to other clients using an unique nickname (9 bytes max lenght).  
Also all the servers need to have the following information about all the clients:  
* the real name of the host that the client is connected.  
* the username of the client of that host.  
* the server that the client is connected.  

### 1.2.1 Operators
Operators are admins.  
SQUIT (4.1.7).  
CONNECT (4.3.5).  
KILL (4.6.1).  

## 1.3 Channels
A channel is a named group containing > 1 clients which recives the channel msgs.  
The channel is implicitly created when the first client joins it.  
The channel is implicitly destroyed when the last client lefts it.  
Until the channel exists any client can refer to this channel using its name.  

Channels names :  
* Are strings.  
* Begin with '&' or '#'.  
* 200 bytes max sized.  
* Can't contain whitespaces.  
* Can't contain ctrl^G (ASCII 7).  
* Can't contain a ','.  
2 kinds of channels can exist:  
* Channels distributed all over the network (all the servers) -> '#'.  
* Local server channel -> '&'.  

MODE (4.2.3).  
To create a new channel or join an existing one, a user must use "JOIN" command.  
The first client to join a channel becomes the operator of the channel.  
Else if the channel already exist: check 8.13.  
If the connection between 2 servers breaks up, for a channel which clients are in both servers, when the connection is restored both servers will anounce to each other all the JOINs and MODEs of the channel.  

### 1.3.1 Channel operator
The channel operator owns the channel.  
It can cast some commands:  
* KICK: kick out of the channel a user.  
* MODE: change channel modes.  
* INVITE: invite a user to the channel.  
* TOPIC: Change the channel topic (requires +t mode).  
Using commands "NAMES", "WHO" or "WHOIS" the operator nickname starts with a '@'.  

======

# 2. The IRC Specification

## 2.2 Chars
Unique bytes are used to send mgs (char, uchar, int8_t, uint8_t, ...).  
Some bytes values are however used as messages delimitors:  
* '{', '}', '|' are lowercases.  
* '[', ']', '\' are uppercases.  

## 2.3 Messages
Servers and clients send to each other messages and those messages can generate or not an answer.  
If a user cast a valid command, the server behaviour should be as specified in the documentation.  
The comunication between client & server is essentally asyncronous.  
Each IRC message can consist on (separeted with at least 1 space):  
* \<optional\> prefix:  
	* start ':' (0x3b) and be followed by the prefix (no spaces between).  
	* is used by severs to indicate the origin of the msg (no prefix == msg comes from same connection as the msg receptor).  
	* Client shouldn't use prefixes for sending msgs, if they do the only valid prefix is the nickname associated with the client.  
	* If the prefix isn't in the database or the prefix or the sender does not match with the msg prefix the server must ignore the msg in a silent way).  
* command: must be an IRC valid command or 3 digits representing ASCII text.  
* parameters: max == 15.  

Each message is finished by CR (0x0d) - LF (0x0a).  
A message max lenght is 512 - CR-LF = 510.  
More details in section 7.  

### 2.3.1 Messages format in pseudocode

\<message\>  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  -> [':' \<prefix\> \<space\> ] \<command\> \<parram\> \<CR-LF\>  
\<prefix\>  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  -> \<server name\> | \<nick\> ['!' \<user\> ] ['@' \<host\> ]  
\<command\>  &nbsp; &nbsp; &nbsp; &nbsp;  -> \<char\> { \<char\> } | \<digit\> \<digit\> \<digit\>  
\<space\>  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  -> ' ' { ' ' } (0x20)  
\<param\>  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  -> \<space\> [':' \<final param\> | \<middle param\> \<final param\> ]  
\<final param\>  &nbsp; &nbsp; &nbsp;  -> any kind of bytes sequence (empty too) exept \<CR-LF\> or 0x0  
\<middle param\>  &nbsp; -> any kind of bytes seqence (not empty) exept \<CR-LF\> or 0x0  
\<CR-LF\>  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  -> 0x0d - 0x0a  

#### *Notes:*
1) \<space\> is only 0x20 not whitespaces.  
2) \<final param\> and \<middle param\> are only used to accept spaces in a param  
	(just a syntactical trick).  
3) CR and LF can't be part of the msg (logical).  
4) 0x0 can't be used inside a msg for C/C++ reasons.  
5) The last \<param\> must be an empty string.  
6) The prefix "['!' \<user\> ] ['@' \<host\> ]" must not be used in	server - server comunication, its only server - client oriented.  

\<target\>  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  -> \<a\> \<"," \<target\>  
\<a\>   &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  -> \<channel\> | \<user\> '@' \<server name\> | \<nick\> | \<mask\>  
\<channel\>   &nbsp; &nbsp; &nbsp; &nbsp;  -> ('#' | '&') \<string\>  
\<server name\> &nbsp; -> \<host\>  
\<host\>   &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; -> see RFC 952 [DNS:4]  
\<mask\>   &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; -> ('#' |'&') \<string\>  
\<string\>   &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  -> any 1bytes value exept: space, bell, cr, lf, coma.  

\<user\>   &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  -> \<string with coma\> { \<string with coma\> }  
\<letter\>   &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; -> 'a' ... 'z' | 'A' ... 'Z'  
\<digit\>   &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; -> '0' ... '9'  
\<especial\>   &nbsp; &nbsp; &nbsp; &nbsp; -> '-' | '[' | ']' | '\' \ '`' | '^' | '{' '}'  

## 2.4 Numeric answers
The most common answer (for error and not error).  
Composed by:  
* 1\) The sender prefix.  
* 2\) 3 digit integer.  
* 3\) The receiver.  

A client can't raise a numeric answer (it's silently ignored).  
Section 6 contains the numeric answers codes list.  

======

# 3. IRC Concepts

## 3.1 One to one comunication
Usualy one to one comunication is only done by clients.  
To ensure a secure way of comunication between clients it's necessary that all the servers are able to send a msg in a precise direction (to any client).  
The shortest path wins.  

## 3.2 One-to-many

### 3.2.1 One to list comunication
Worts groupal method (send message N times for N members in the list).  

### 3.2.2 One to a group (channel) comunication
The conversation is only sent to servers used by the users of the channel.  
If there are more than 1 user in the same server and in the same channel, the	message is sent once to the server.  

### 3.2.3 One to host/server mask comunication
Same as previous.  

## 3.3 One-to-all

### 3.3.1 Client to client comunication
There's any kind of unique message that can be sent to all the clients.  

### 3.3.2 Client to server comunication
Commands change the state of a channel, a user ...  
Must be sent to all the servers all over the network.  

### 3.3.3 Server to server comunication
Almost every msg sent server to server is distributed all over the network to all servers.  

======

# 4. Message details

## 4.1 Connection Registration

The recommended order for a client to register is as follows:
* 1\. Pass message
* 2\. Nick message
* 3\. User message

Command: **PASS**  
	Parameters: \<password\>  
	Example:  
&nbsp; &nbsp; \- PASS secretpasswordhere  

Command: **NICK**  
   Parameters: \<nickname\> [ \<hopcount\> ]  
   Example:  
&nbsp; &nbsp; \- *NICK Wiz*
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Introducing new nick "Wiz".  
&nbsp; &nbsp; \- *:WiZ NICK Kilroy*
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; WiZ changed his nickname to Kilroy.  

Command: **USER**  
   Parameters: \<username\> \<hostname\> \<servername\> \<realname\>  
   Examples:  
&nbsp; &nbsp; \- *USER guest tolmoon tolsun :Ronnie Reagan*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  User registering themselves with a username of "guest" and real name "Ronnie Reagan".  
&nbsp; &nbsp; \- *:testnick USER guest tolmoon tolsun :Ronnie Reagan*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  message between servers with the nickname for which the USER command belongs to  


Command: **SERVER**  
   Parameters: \<servername\> \<hopcount\> \<info\>  
   Example:  
&nbsp; &nbsp; \- *SERVER test.oulu.fi 1 :[tolsun.oulu.fi] Experimental server*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; New server test.oulu.fi introducing itself and attempting to register. The name in []'s is the hostname for the host running test.oulu.fi.  
&nbsp; &nbsp; \- *:tolsun.oulu.fi SERVER csd.bu.edu 5 :BU Central Server*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Server tolsun.oulu.fi is our uplink for csd.bu.edu which is 5 hops away.  

Command: **OPER**  
   Parameters: \<user\> \<password\>  
   Example:  
&nbsp; &nbsp; \- *OPER foo bar*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Attempt to register as an operator using a username of "foo" and "bar" as the password.  

Command: **QUIT**  
   Parameters: [\<Quit message\>]  
   Examples:  
&nbsp; &nbsp; \- *QUIT :Gone to have lunch*
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Preferred message format.  

Command: **SQUIT**  
   Parameters: \<server\> \<comment\>  
   Example:  
&nbsp; &nbsp; \- *SQUIT tolsun.oulu.fi :Bad Link ?*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; the server link tolson.oulu.fi has been terminated because of "Bad Link".  
&nbsp; &nbsp; \- *:Trillian SQUIT cm22.eng.umd.edu :Server out of control*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; message from Trillian to disconnect "cm22.eng.umd.edu" from the net because "Server out of control".  


## 4.2 Channel operations

Command: **JOIN**  
   Parameters: \<channel\>{,\<channel\>} [\<key\>{,\<key\>}]  
   Examples:  
 &nbsp; &nbsp; \- *JOIN #foobar*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; join channel #foobar.  
 &nbsp; &nbsp; \- *JOIN &foo fubar*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; join channel &foo using key "fubar".  
 &nbsp; &nbsp; \- *JOIN #foo,&bar fubar*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; join channel #foo using key "fubar" and &bar using no key.  
&nbsp; &nbsp; \- *JOIN #foo,#bar fubar,foobar*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; join channel #foo using key "fubar". and channel #bar using key "foobar".  
&nbsp; &nbsp; \- *JOIN #foo,#bar*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; join channels #foo and #bar.  
&nbsp; &nbsp; \- *:WiZ JOIN #Twilight_zone*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; JOIN message from WiZ  

Command: **PART**  
   Parameters: \<channel\>{,\<channel\>}  
   Examples:  
&nbsp; &nbsp; \- *PART #twilight_zone*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; leave channel "#twilight_zone"  
&nbsp; &nbsp; \- *PART #oz-ops,&group5*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; leave both channels "&group5" and "#oz-ops".  

   Channel mode Parameters: \<channel\> {[+|-]|o|p|s|i|t|n|b|v} [\<limit\>] [\<user\>] [\<ban mask\>]  

   User mode Parameters: \<nickname\> {[+|-]|i|w|s|o}  

   Examples - Use of Channel Modes:  
&nbsp; &nbsp; \- *MODE #Finnish +im*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Makes #Finnish channel moderated and 'invite-only'.  
&nbsp; &nbsp; \- *MODE #Finnish +o Kilroy*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Gives 'chanop' privileges to Kilroy on channel #Finnish.  
&nbsp; &nbsp; \- *MODE #Finnish +v Wiz*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Allow WiZ to speak on #Finnish.  
&nbsp; &nbsp; \- *MODE #Fins -s*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Removes 'secret' flag from channel #Fins.  
&nbsp; &nbsp; \- *MODE #42 +k oulu*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Set the channel key to "oulu".  
&nbsp; &nbsp; \- *MODE #eu-opers +l 10*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Set the limit for the number of users on channel to 10.  
&nbsp; &nbsp; \- *MODE &oulu +b*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; list ban masks set for channel.  
&nbsp; &nbsp; \- *MODE &oulu +b \*!\*@**  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; prevent all users from joining.  
&nbsp; &nbsp; \- *MODE &oulu +b \*!\*@\*.edu*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; prevent any user from a hostname matching *.edu from joining.  

    Examples - Use of User Modes:  
&nbsp; &nbsp; \- *:MODE WiZ -w*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; turns reception of WALLOPS messages off for WiZ.  
&nbsp; &nbsp; \- *:Angel MODE Angel +i*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Message from Angel to make themselves invisible.  
&nbsp; &nbsp; \- *MODE WiZ -o*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; WiZ 'deopping' (removing operator status). The plain reverse of this command ("MODE WiZ +o") must not be allowed from users since would bypass the OPER command.  

Command: **TOPIC**  
   Parameters: \<channel\> [\<topic\>]  
   Examples:  
&nbsp; &nbsp; \- *:Wiz TOPIC #test :New topic*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ;User Wiz setting the topic.  
&nbsp; &nbsp; \- *TOPIC #test :another topic*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ;set the topic on #test to "another topic".  
&nbsp; &nbsp; \- *TOPIC #test*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; check the topic for #test.  

Command: **NAMES**  
   Parameters: [\<channel\>{,\<channel\>}]  
   Examples:  
&nbsp; &nbsp; \- *NAMES #twilight_zone,#42*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; list visible users on #twilight_zone and #42 if the channels are visible to you.  
&nbsp; &nbsp; \- *NAMES*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; list all visible channels and users  


Command: **LIST**  
   Parameters: [\<channel\>{,\<channel\>} [\<server\>]]  
   Examples:  
&nbsp; &nbsp; \- *LIST*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; List all channels.  
&nbsp; &nbsp; \- *LIST #twilight_zone,#42*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; List channels #twilight_zone and #42  


Command: **INVITE**  
   Parameters: \<nickname\> \<channel\>  
   Examples:  
&nbsp; &nbsp; \- *:Angel INVITE Wiz #Dust*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; User Angel inviting WiZ to channel #Dust  
&nbsp; &nbsp; \- *INVITE Wiz #Twilight_Zone*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Command to invite WiZ to #Twilight_zone  

Command: **KICK**  
   Parameters: \<channel\> \<user\> [\<comment\>]  
   Examples:  
&nbsp; &nbsp; \- *KICK &Melbourne Matthew*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Kick Matthew from &Melbourne  
&nbsp; &nbsp; \- *KICK #Finnish John :Speaking English*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Kick John from #Finnish using "Speaking English" as the reason (comment).  
&nbsp; &nbsp; \- *:WiZ KICK #Finnish John*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; KICK message from WiZ to remove John from channel #Finnish  

*NOTE:*
     It is possible to extend the KICK command parameters to the following:  
 &nbsp; &nbsp; &nbsp; &nbsp; \<channel\>{,\<channel\>} \<user\>{,\<user\>} [\<comment\>]  


## 4.3 Server queries and commands

Command: **VERSION**  
   Parameters: [\<server\>]  
   Examples:  
&nbsp; &nbsp; \- *:Wiz VERSION \*.se*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; message from Wiz to check the version of a server matching "*.se"  
&nbsp; &nbsp; \- *VERSION tolsun.oulu.fi*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; check the version of server "tolsun.oulu.fi".  

Command: **STATS**  
   Parameters: [\<query\> [\<server\>]]  
   Examples:  
&nbsp; &nbsp; \- *STATS m*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; check the command usage for the server you are connected to  
&nbsp; &nbsp; \- *:Wiz STATS c eff.org*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; request by WiZ for C/N line information from server eff.org  

Command: **LINKS**  
   Parameters: [[\<remote server\>] \<server mask\>]  
   Examples:  
&nbsp; &nbsp; \- *LINKS *.au*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; list all servers which have a name that matches *.au;  
&nbsp; &nbsp; \- *:WiZ LINKS \*.bu.edu \*.edu*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; LINKS message from WiZ to the first server matching *.edu for a list of servers matching *.bu.edu.  

Command: **TIME**  
   Parameters: [\<server\>]  
   Examples:  
   &nbsp; &nbsp; \- *TIME tolsun.oulu.fi*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; check the time on the server "tolson.oulu.fi"  
   &nbsp; &nbsp; \- *Angel TIME \*.au*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; user angel checking the time on a  
 
Command: **CONNECT**  
   Parameters: \<target server\> [\<port\> [\<remote server\>]]  
   Examples:  
&nbsp; &nbsp; \- *CONNECT tolsun.oulu.fi*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Attempt to connect a server to tolsun.oulu.fi  
&nbsp; &nbsp; \- *:WiZ CONNECT eff.org 6667 csd.bu.edu*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; CONNECT attempt by WiZ to get servers eff.org and csd.bu.edu connected on port 6667.  

Command: **TRACE**  
   Parameters: [\<server\>]  
   Examples:  
&nbsp; &nbsp; \- *TRACE \*.oulu.fi*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; TRACE to a server matching *.oulu.fi  
&nbsp; &nbsp; \- *:WiZ TRACE AngelDust*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; TRACE issued by WiZ to nick AngelDust  


Command: **ADMIN**  
   Parameters: [\<server\>]  
   Examples:  
&nbsp; &nbsp; \- *ADMIN tolsun.oulu.fi*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; request an ADMIN reply from tolsun.oulu.fi  
&nbsp; &nbsp; \- *:WiZ ADMIN \*.edu*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; ADMIN request from WiZ for first server found to match *.edu.  

Command: **INFO**  
   Parameters: [\<server\>]  
   Examples:  
&nbsp; &nbsp; \- *INFO csd.bu.edu*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; request an INFO reply from csd.bu.edu  
&nbsp; &nbsp; \- *:Avalon INFO \*.fi*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; INFO request from Avalon for first server found to match *.fi.  
&nbsp; &nbsp; \- *INFO Angel*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; request info from the server that Angel is connected to.  


## 4.4 Sending messages

The main purpose of the IRC protocol is to provide a base for clients to communicate with each other.  

PRIVMSG and NOTICE are the only messages available which actually perform delivery of a text message from one client to another - the rest just make it possible and try to ensure it happens in a reliable and structured manner.  

### 4.4.1 Private messages

Command: **PRIVMSG**  
   Parameters: \<receiver\>{,\<receiver\>} \<text to be sent\>  
   Examples:  
&nbsp; &nbsp; \- *:Angel PRIVMSG Wiz :Hello are you receiving this message ?*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Message from Angel to Wiz.  
&nbsp; &nbsp; \- *PRIVMSG Angel :yes I'm receiving it !receiving it !'u\>(768u+1n) .br*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ;Message to Angel.  
&nbsp; &nbsp; \- *PRIVMSG jto@tolsun.oulu.fi :Hello !*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Message to a client on server tolsun.oulu.fi with username of "jto".  
&nbsp; &nbsp; \- *PRIVMSG $*.fi :Server tolsun.oulu.fi rebooting.*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Message to everyone on a server which has a name matching *.fi.  
&nbsp; &nbsp; \- *PRIVMSG #*.edu :NSFNet is undergoing work, expect interruptions*  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Message to all users who come from a host which has a name matching *.edu.  

### 4.4.2 Notice

Command: **NOTICE**  
   Parameters: \<nickname\> \<text\>  


## 4.5 User based queries

Command: **WHO**   
   Parameters: [\<name\> [\<o\>]]  
   Examples:  
&nbsp; &nbsp; \- *WHO \*.fi*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; List all users who match against "*.fi".  
&nbsp; &nbsp; \- *WHO jto\* o*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; List all users with a match against "jto*" if they are an operator.  

Command: **WHOIS**   
   Parameters: [\<server\>] \<nickmask\>[,\<nickmask\>[,...]]  
   Examples:  
&nbsp; &nbsp; \- *WHOIS wiz*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; return available user information about nick WiZ*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; ask server eff.org for user information about trillian  


Command: **WHOWAS**   
   Parameters: \<nickname\> [\<count\> [\<server\>]]  
   Examples:  
&nbsp; &nbsp; \- *WHOWAS Wiz*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; return all information in the nick history about nick "WiZ";  
&nbsp; &nbsp; \- *WHOWAS Mermaid 9*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; return at most, the 9 most recent entries in the nick history for "Mermaid";    
&nbsp; &nbsp; \- *WHOWAS Trillian 1 \*.edu*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; return the most recent history for "Trillian" from the first server found to match "*.edu".  


## 4.6 Miscellaneous messages

   Messages in this category do not fit into any of the above categories but are nonetheless still a part of and required by the protocol.  

Command: **KILL**  
   Parameters: \<nickname\> \<comment\>  

	The KILL message is used to cause a client-server connection to be closed by the server which has the actual connection.  
	KILL is used by servers when they encounter a duplicate entry in the list of valid nicknames and is used to remove both entries.  
	It is also available to operators.  

	Clients which have automatic reconnect algorithms effectively make this command useless since the disconnection is only brief.  
	It does however break the flow of data and can be used to stop large amounts of being abused, any user may elect to receive KILL messages generated for others to keep an 'eye' on would be trouble spots.  

	In an arena where nicknames are required to be globally unique at all times, KILL messages are sent whenever 'duplicates' are detected (that is an attempt to register two users with the same nickname) in the hope that both of them will disappear and only 1 reappear.  

	The comment given must reflect the actual reason for the KILL.  
	For server-generated KILLs it usually is made up of details concerning the origins of the two conflicting nicknames.  
	For users it is left up to them to provide an adequate reason to satisfy others who see it.  
	To prevent/discourage fake KILLs from being generated to hide the identify of the KILLer, the comment also shows a 'kill-path' which is updated by each server it passes through, each prepending its name to the path.  
  
  
	Examples:  
&nbsp; &nbsp; \- *KILL David (csd.bu.edu \<- tolsun.oulu.fi)*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Nickname collision between csd.bu.edu and tolson.oulu.fi  


   *NOTE:*
   It is recommended that only Operators be allowed to kill other users with KILL message. In an ideal world not even operators would need to do this and it would be left to servers to deal with.  


Command: **PING**  
   Parameters: \<server1\> [\<server2\>]  
   Examples:  
&nbsp; &nbsp; \- *PING tolsun.oulu.fi*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; server sending a PING message to another server to indicate it is still alive.  
&nbsp; &nbsp; \- *PING WiZ*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; PING message being sent to nick WiZ  

Command: **PONG**  
   Parameters: \<daemon\> [\<daemon2\>]  
   Examples:  
&nbsp; &nbsp; \- *PONG csd.bu.edu tolsun.oulu.fi*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; PONG message from csd.bu.edu to  

Command: **ERROR**  
   Parameters: \<error message\>  
   Examples:  
&nbsp; &nbsp; \- *ERROR :Server \*.fi already exists*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; ERROR message to the other server which caused this error.  
&nbsp; &nbsp; \- *NOTICE WiZ :ERROR from csd.bu.edu -- Server \*.fi already exists*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Same ERROR message as above but sent to user WiZ on the other server.  

======




# Sources:
* [RFC 1459 documentation](https://tools.ietf.org/html/rfc1459)
* [RFC 2810 documentation](https://tools.ietf.org/html/rfc2810)
* [RFC 2811 documentation](https://tools.ietf.org/html/rfc2811)
* [RFC 2812 documentation](https://tools.ietf.org/html/rfc2812)
* [RFC 2813 documentation](https://tools.ietf.org/html/rfc2813)
* [RFC 7194 documentation](https://tools.ietf.org/html/rfc7194)

