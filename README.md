
This file contains the following RFC documentation summary:  
* **RFC 1459 (May 1993)**
* **RFC 2810 - 2811 - 2812 - 2813 (April 2000)**
* **RFC 7194 (August 2014)**

**RFC 1459**: Basic Internet Relay Chat Protocol

**RFC 2810 to 2813**: Update of RFC 1459 describing the architecture of the IRC protocol and the role of its different components.  
Details:  
* RFC 2810: Architecture
* RFC 2811: Channel Management
* RFC 2812: Client Protocol
* RFC 2813: Server Protocol

**RFC 7194**: Default Port for Internet Relay Chat (IRC) via TLS/SSL

------------------------------------------------------------

# Summary

**RFC 1459 (May 1993)**

[1. RFC 1459 - Introduction](#1-rfc-1459---introduction)  
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
* [4.5 User based queries](#45-user-based-queries)  
* [4.6 Miscellaneous messages](#46-miscellaneous-messages)  

[5. OPTIONALS](#5-optionals)  

[6. REPLIES](#6-replies)  
* [6.1 Error Replies](#61-error-replies)  
* [6.2 Command responses](#62-command-responses)  
* [6.3 Reserved numerics](#63-reserved-numerics)  

[7. Client and server authentication](#7-client-and-server-authentication)  

[8. Current implementations](#8-current-implementations)  
* [8.1 Network protocol: TCP - why it is best used here](#81-network-protocol-tcp---why-it-is-best-used-here)  
* [8.2 Command Parsing](#82-command-parsing)  
* [8.3 Message delivery](#83-message-delivery)  
* [8.4 Connection 'Liveness'](#84-connection-liveness)  
* [8.5 Establishing a server to client connection](#85-establishing-a-server-to-client-connection)  
* [8.6 Establishing a server-server connection](#86-establishing-a-server-server-connection)  
* [8.7 Terminating server-client connections](#87-terminating-server-client-connections)  
* [8.8 Terminating server-server connections](#88-terminating-server-server-connections)  
* [8.9 Tracking nickname changes](#89-tracking-nickname-changes)  
* [8.10 Flood control of clients](#810-flood-control-of-clients)  
* [8.11 Non-blocking lookups](#811-non-blocking-lookups)  
* [8.12 Configuration File](#812-configuration-file)  
* [8.13 Channel membership](#813-channel-membership)  

[9. Current problems](#9-current-problems)  
* [9.1 Scalability](#91-scalability)  
* [9.2 Labels](#92-labels)  
* [9.3 Algorithms](#93-algorithms)  
  
  
  
**RFC 2810 (April 2000)**

[1. Introduction](#1-rfc-2810---introduction)  

[2. Components](#2-components)  
* [2.2 Clients](#22-clients)  

[4. IRC Protocol Services](#4-irc-protocol-services)  
* [4.1 Client Locator](#41-client-locator)  
* [4.2 Message Relaying](#42-message-relaying)  
* [4.3 Channel Hosting And Management](#43-channel-hosting-and-management)  

[6. Current Problems](#6-current-problems)  
* [6.1 Scalability](#61-scalability)  
* [6.2 Reliability](#62-reliability)  
* [6.3 Network Congestion](#63-network-congestion)  
* [6.4 Privacy](#64-privacy)  




[Sources](#Sources)  

------------------------------------------------------------

# **RFC 1459 (May 1993)**

# 1. RFC 1459 - Introduction

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

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; *[to the top](#summary)*

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

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; *[to the top](#summary)*

# 3. IRC Concepts

## 3.1 One to one comunication
Usualy one to one comunication is only done by clients.  
To ensure a secure way of comunication between clients it's necessary that all the servers are able to send a msg in a precise direction (to any client).  
The shortest path wins.  

## 3.2 One-to-many

### 3.2.1 One to list comunication
Worst groupal method (send message N times for N members in the list).  

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

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; *[to the top](#summary)*

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

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; *[to the top](#summary)*

# 5. OPTIONALS

This section describes OPTIONAL messages. They are not required in a working server implementation of the protocol described herein.  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; *[to the top](#summary)*

# 6. REPLIES

## 6.1 Error Replies

401 &nbsp; &nbsp; ERR_NOSUCHNICK  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<nickname\> :No such nick/channel"  

402 &nbsp; &nbsp; ERR_NOSUCHSERVER  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<server name\> :No such server"  

403 &nbsp; &nbsp; ERR_NOSUCHCHANNEL  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<channel name\> :No such channel"  

404 &nbsp; &nbsp; ERR_CANNOTSENDTOCHAN  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<channel name\> :Cannot send to channel"  

405 &nbsp; &nbsp; ERR_TOOMANYCHANNELS  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<channel name\> :You have joined too many channels"  

406 &nbsp; &nbsp; ERR_WASNOSUCHNICK  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<nickname\> :There was no such nickname"  

407 &nbsp; &nbsp; ERR_TOOMANYTARGETS  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<target\> :Duplicate recipients. No message    

409 &nbsp; &nbsp; ERR_NOORIGIN  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":No origin specified"  

411 &nbsp; &nbsp; ERR_NORECIPIENT  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":No recipient given (\<command\>)"  

412 &nbsp; &nbsp; ERR_NOTEXTTOSEND  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":No text to send"  

413 &nbsp; &nbsp; ERR_NOTOPLEVEL  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<mask\> :No toplevel domain specified"  

414 &nbsp; &nbsp; ERR_WILDTOPLEVEL  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<mask\> :Wildcard in toplevel domain"  

421 &nbsp; &nbsp; ERR_UNKNOWNCOMMAND  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<command\> :Unknown command"  

422 &nbsp; &nbsp; ERR_NOMOTD  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":MOTD File is missing"  

423 &nbsp; &nbsp; ERR_NOADMININFO  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<server\> :No administrative info available"  

424 &nbsp; &nbsp; ERR_FILEERROR  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":File error doing \<file op\> on \<file\>"  

431 &nbsp; &nbsp; ERR_NONICKNAMEGIVEN  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":No nickname given"  

432 &nbsp; &nbsp; ERR_ERRONEUSNICKNAME  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<nick\> :Erroneus nickname"  

433 &nbsp; &nbsp; ERR_NICKNAMEINUSE  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<nick\> :Nickname is already in use"  

436 &nbsp; &nbsp; ERR_NICKCOLLISION  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<nick\> :Nickname collision KILL"  

441 &nbsp; &nbsp; ERR_USERNOTINCHANNEL  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<nick\> \<channel\> :They aren't on that channel"  

442 &nbsp; &nbsp; ERR_NOTONCHANNEL  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<channel\> :You're not on that channel"  

443 &nbsp; &nbsp; ERR_USERONCHANNEL  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<user\> \<channel\> :is already on channel"  

444 &nbsp; &nbsp; ERR_NOLOGIN  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<user\> :User not logged in"  

445 &nbsp; &nbsp; ERR_SUMMONDISABLED  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":SUMMON has been disabled"  

446 &nbsp; &nbsp; ERR_USERSDISABLED  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":USERS has been disabled"  

451 &nbsp; &nbsp; ERR_NOTREGISTERED  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":You have not registered"  

461 &nbsp; &nbsp; ERR_NEEDMOREPARAMS  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<command\> :Not enough parameters"  

462 &nbsp; &nbsp; ERR_ALREADYREGISTRED  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":You may not reregister"  


463 &nbsp; &nbsp; ERR_NOPERMFORHOST  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":Your host isn't among the privileged"  

464 &nbsp; &nbsp; ERR_PASSWDMISMATCH  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":Password incorrect"  

465 &nbsp; &nbsp; ERR_YOUREBANNEDCREEP  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":You are banned from this server"  

467 &nbsp; &nbsp; ERR_KEYSET  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<channel\> :Channel key already set"  

471 &nbsp; &nbsp; ERR_CHANNELISFULL  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<channel\> :Cannot join channel (+l)"  

472 &nbsp; &nbsp; ERR_UNKNOWNMODE  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<char\> :is unknown mode char to me"  

473 &nbsp; &nbsp; ERR_INVITEONLYCHAN  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<channel\> :Cannot join channel (+i)"  

474 &nbsp; &nbsp; ERR_BANNEDFROMCHAN  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<channel\> :Cannot join channel (+b)"  

475 &nbsp; &nbsp; ERR_BADCHANNELKEY  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<channel\> :Cannot join channel (+k)"  

481 &nbsp; &nbsp; ERR_NOPRIVILEGES  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":Permission Denied- You're not an IRC operator"  

482 &nbsp; &nbsp; ERR_CHANOPRIVSNEEDED  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<channel\> :You're not channel operator"  

483 &nbsp; &nbsp; ERR_CANTKILLSERVER  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":You cant kill a server!"  

491 &nbsp; &nbsp; ERR_NOOPERHOST  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":No O-lines for your host"  

501 &nbsp; &nbsp; ERR_UMODEUNKNOWNFLAG  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":Unknown MODE flag"  

502 &nbsp; &nbsp; ERR_USERSDONTMATCH  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":Cant change mode for other users"


## 6.2 Command responses

300 &nbsp; &nbsp; RPL_NONE  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; Dummy reply number. Not used.  

302 &nbsp; &nbsp; RPL_USERHOST  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":[\<reply\>{\<space\>\<reply\>}]"  

303 &nbsp; &nbsp; RPL_ISON  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":[\<nick\> {\<space\>\<nick\>}]"  

301 &nbsp; &nbsp; RPL_AWAY  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<nick\> :\<away message\>"  

305 &nbsp; &nbsp; RPL_UNAWAY  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":You are no longer marked as being away"  
306 &nbsp; &nbsp; RPL_NOWAWAY  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":You have been marked as being away"  

311 &nbsp; &nbsp; RPL_WHOISUSER  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<nick\> \<user\> \<host\> * :\<real name\>"  
312 &nbsp; &nbsp; RPL_WHOISSERVER  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<nick\> \<server\> :\<server info\>"  
313 &nbsp; &nbsp; RPL_WHOISOPERATOR  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<nick\> :is an IRC operator"  
317 &nbsp; &nbsp; RPL_WHOISIDLE  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<nick\> \<integer\> :seconds idle"  
318 &nbsp; &nbsp; RPL_ENDOFWHOIS  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<nick\> :End of /WHOIS list"  
319 &nbsp; &nbsp; RPL_WHOISCHANNELS  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<nick\> :{[@|+]\<channel\>\<space\>}"  

314 &nbsp; &nbsp; RPL_WHOWASUSER  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<nick\> \<user\> \<host\> * :\<real name\>"  
369 &nbsp; &nbsp; RPL_ENDOFWHOWAS  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<nick\> :End of WHOWAS"  

321 &nbsp; &nbsp; RPL_LISTSTART  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "Channel :Users  Name"  
322 &nbsp; &nbsp; RPL_LIST  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<channel\> \<# visible\> :\<topic\>"  
323 &nbsp; &nbsp; RPL_LISTEND  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":End of /LIST"  

324 &nbsp; &nbsp; RPL_CHANNELMODEIS  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<channel\> \<mode\> \<mode params\>"  

331 &nbsp; &nbsp; RPL_NOTOPIC  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<channel\> :No topic is set"  
332 &nbsp; &nbsp; RPL_TOPIC  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<channel\> :\<topic\>"  

341 &nbsp; &nbsp; RPL_INVITING  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<channel\> \<nick\>"  

342 &nbsp; &nbsp; RPL_SUMMONING  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<user\> :Summoning user to IRC"  

351 &nbsp; &nbsp; RPL_VERSION  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<version\>.\<debuglevel\> \<server\> :\<comments\>"  

352 &nbsp; &nbsp; RPL_WHOREPLY  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<channel\> \<user\> \<host\> \<server\> \<nick\> \<H|G\>[*][@|+] :\<hopcount\> \<real name\>"  
315 &nbsp; &nbsp; RPL_ENDOFWHO  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<name\> :End of /WHO list"  

353 &nbsp; &nbsp; RPL_NAMREPLY  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<channel\> :[[@|+]\<nick\> [[@|+]\<nick\> [...]]]"  
366 &nbsp; &nbsp; RPL_ENDOFNAMES  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<channel\> :End of /NAMES list"  

364 &nbsp; &nbsp; RPL_LINKS  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<mask\> \<server\> :\<hopcount\> \<server info\>"  
365 &nbsp; &nbsp; RPL_ENDOFLINKS  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<mask\> :End of /LINKS list"  

367 &nbsp; &nbsp; RPL_BANLIST  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<channel\> \<banid\>"  
368 &nbsp; &nbsp; RPL_ENDOFBANLIST  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<channel\> :End of channel ban list"  

371 &nbsp; &nbsp; RPL_INFO  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":\<string\>"  
374 &nbsp; &nbsp; RPL_ENDOFINFO  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":End of /INFO list"  

375 &nbsp; &nbsp; RPL_MOTDSTART  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":- \<server\> Message of the day - "  
372 &nbsp; &nbsp; RPL_MOTD  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":- \<text\>"  
376 &nbsp; &nbsp; RPL_ENDOFMOTD  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":End of /MOTD command"  

381 &nbsp; &nbsp; RPL_YOUREOPER  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":You are now an IRC operator"  

382 &nbsp; &nbsp; RPL_REHASHING  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<config file\> :Rehashing"  

391 &nbsp; &nbsp; RPL_TIME  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<server\> :\<string showing server's local time\>"  

392 &nbsp; &nbsp; RPL_USERSSTART  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":UserID   Terminal  Host"  
393 &nbsp; &nbsp; RPL_USERS  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":%-8s %-9s %-8s"  
394 &nbsp; &nbsp; RPL_ENDOFUSERS  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":End of users"  
395 &nbsp; &nbsp; RPL_NOUSERS  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":Nobody logged in"  

200 &nbsp; &nbsp; RPL_TRACELINK  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "Link \<version & debug level\> \<destination\> \<next server\>"  
201 &nbsp; &nbsp; RPL_TRACECONNECTING  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "Try. \<class\> \<server\>"  
202 &nbsp; &nbsp; RPL_TRACEHANDSHAKE  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "H.S. \<class\> \<server\>"  
203 &nbsp; &nbsp; RPL_TRACEUNKNOWN  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "???? \<class\> [\<client IP address in dot form\>]"  
204 &nbsp; &nbsp; RPL_TRACEOPERATOR  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "Oper \<class\> \<nick\>"  
205 &nbsp; &nbsp; RPL_TRACEUSER  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "User \<class\> \<nick\>"  
206 &nbsp; &nbsp; RPL_TRACESERVER  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "Serv \<class\> \<int\>S \<int\>C \<server\> \<nick!user|*!*\>@\<host|server\>"  
208 &nbsp; &nbsp; RPL_TRACENEWTYPE  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<newtype\> 0 \<client name\>"  
261 &nbsp; &nbsp; RPL_TRACELOG  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "File \<logfile\> \<debug level\>"  

211 &nbsp; &nbsp; RPL_STATSLINKINFO  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<linkname\> \<sendq\> \<sent messages\> \<sent bytes\> \<received messages\> \<received bytes\> \<time open\>"  
212 &nbsp; &nbsp; RPL_STATSCOMMANDS  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<command\> \<count\>"  
213 &nbsp; &nbsp; RPL_STATSCLINE  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "C \<host\> * \<name\> \<port\> \<class\>"  
214 &nbsp; &nbsp; RPL_STATSNLINE  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "N \<host\> * \<name\> \<port\> \<class\>"  
215 &nbsp; &nbsp; RPL_STATSILINE  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "I \<host\> * \<host\> \<port\> \<class\>"  
216 &nbsp; &nbsp; RPL_STATSKLINE  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "K \<host\> * \<username\> \<port\> \<class\>"  
218 &nbsp; &nbsp; RPL_STATSYLINE  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "Y \<class\> \<ping frequency\> \<connect frequency\> \<max sendq\>"  
219 &nbsp; &nbsp; RPL_ENDOFSTATS  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<stats letter\> :End of /STATS report"  
241 &nbsp; &nbsp; RPL_STATSLLINE  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "L \<hostmask\> * \<servername\> \<maxdepth\>"  
242 &nbsp; &nbsp; RPL_STATSUPTIME  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":Server Up %d days %d:%02d:%02d"  
243 &nbsp; &nbsp; RPL_STATSOLINE  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "O \<hostmask\> * \<name\>"  
244 &nbsp; &nbsp; RPL_STATSHLINE  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "H \<hostmask\> * \<servername\>"  

221 &nbsp; &nbsp; RPL_UMODEIS  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<user mode string\>"  

251 &nbsp; &nbsp; RPL_LUSERCLIENT  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":There are \<integer\> users and \<integer\> invisible on \<integer\> servers"  
252 &nbsp; &nbsp; RPL_LUSEROP  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<integer\> :operator(s) online"  
253 &nbsp; &nbsp; RPL_LUSERUNKNOWN  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<integer\> :unknown connection(s)"  
254 &nbsp; &nbsp; RPL_LUSERCHANNELS  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<integer\> :channels formed"  
255 &nbsp; &nbsp; RPL_LUSERME  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":I have \<integer\> clients and \<integer\> servers"  

256 &nbsp; &nbsp; RPL_ADMINME  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<server\> :Administrative info"  
257 &nbsp; &nbsp; RPL_ADMINLOC1  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":\<admin info\>"  
258 &nbsp; &nbsp; RPL_ADMINLOC2  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":\<admin info\>"  
259 &nbsp; &nbsp; RPL_ADMINEMAIL  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ":\<admin info\>"

## 6.3 Reserved numerics

These numerics are not described above since they fall into one of the following categories:  
&nbsp; &nbsp; &nbsp; &nbsp; 1\. no longer in use;  
&nbsp; &nbsp; &nbsp; &nbsp; 2\. reserved for future planned use;  
&nbsp; &nbsp; &nbsp; &nbsp; 3\. in current use but are part of a non-generic 'feature' of the current IRC server.  

        209     RPL_TRACECLASS          217     RPL_STATSQLINE
        231     RPL_SERVICEINFO         232     RPL_ENDOFSERVICES
        233     RPL_SERVICE             234     RPL_SERVLIST
        235     RPL_SERVLISTEND
        316     RPL_WHOISCHANOP         361     RPL_KILLDONE
        362     RPL_CLOSING             363     RPL_CLOSEEND
        373     RPL_INFOSTART           384     RPL_MYPORTIS
        466     ERR_YOUWILLBEBANNED     476     ERR_BADCHANMASK
        492     ERR_NOSERVICEHOST

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; *[to the top](#summary)*

# 7. Client and server authentication

Clients and servers are both subject to the same level of authentication.  

For both, an IP number to hostname lookup (and reverse check on this) is performed for all connections made to the server.  
Both connections are then subject to a password check (if there is a password set for that connection).  
These checks are possible on all connections although the password check is only commonly used with servers.  

An additional check that is becoming of more and more common is that of the username responsible for making the connection.  
Finding the username of the other end of the connection typically involves connecting to an authentication server such as IDENT as described in RFC 1413.  

Given that without passwords it is not easy to reliably determine who is on the other end of a network connection, use of passwords is strongly recommended on inter-server connections in addition to any other measures such as using an ident server.  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; *[to the top](#summary)*

# 8. Current implementations

The only current implementation of this protocol is the IRC server, version 2.8. Earlier versions may implement some or all of the commands described by this document with NOTICE messages replacing many of the numeric replies.  
Unfortunately, due to backward compatibility requirements, the implementation of some parts of this document varies with what is laid out.  
On notable difference is:  
* recognition that any LF or CR anywhere in a message marks the end of that message (instead of requiring CR-LF);  

The rest of this section deals with issues that are mostly of importance to those who wish to implement a server but some parts also apply directly to clients as well.  

## 8.1 Network protocol: TCP - why it is best used here.

IRC has been implemented on top of TCP since TCP supplies a reliable network protocol which is well suited to this scale of conferencing.
The use of multicast IP is an alternative, but it is not widely available or supported at the present time.  

### 8.1.1 Support of Unix sockets  

Given that Unix domain sockets allow listen/connect operations, the current implementation can be configured to listen and accept both client and server connections on a Unix domain socket.  
These are recognized as sockets where the hostname starts with a '/'.  

When providing any information about the connections on a Unix domain socket, the server is required to supplant the actual hostname in place of the pathname unless the actual socket name is being asked for.  

## 8.2 Command Parsing  

To provide useful 'non-buffered' network IO for clients and servers, each connection is given its own private 'input buffer' in which the results of the most recent read and parsing are kept.  
A buffer size of 512 bytes is used so as to hold 1 full message, although, this will usually hold several commands.  
The private buffer is parsed after every read operation for valid messages.  
When dealing with multiple messages from one client in the buffer, care should be taken in case one happens to cause the client to be 'removed'.  

## 8.3 Message delivery  

It is common to find network links saturated or hosts to which you are sending data unable to send data.  
Although Unix typically handles this through the TCP window and internal buffers, the server often has large amounts of data to send (especially when a new server-server link forms) and the small buffers provided in the kernel are not enough for the outgoing queue.  
To alleviate this problem, a "send queue" is used as a FIFO queue for data to be sent. A typical "send queue" may grow to 200 Kbytes on a large IRC network with a slow network connection when a new server connects.  

When polling its connections, a server will first read and parse all incoming data, queuing any data to be sent out. When all available input is processed, the queued data is sent. This reduces the number of write() system calls and helps TCP make bigger packets.  

## 8.4 Connection 'Liveness'  

To detect when a connection has died or become unresponsive, the server must ping each of its connections that it doesn't get a response from in a given amount of time.  

If a connection doesn't respond in time, its connection is closed using the appropriate procedures.  
A connection is also dropped if its sendq grows beyond the maximum allowed, because it is better to close a slow connection than have a server process block.  

## 8.5 Establishing a server to client connection  

Upon connecting to an IRC server, a client is sent the MOTD (if present) as well as the current user/server count (as per the LUSER command).  
The server is also required to give an unambiguous message to the client which states its name and version as well as any other introductory messages which may be deemed appropriate.  

After dealing with this, the server must then send out the new user's nickname and other information as supplied by itself (USER command) and as the server could discover (from DNS/authentication servers).  
The server must send this information out with NICK first followed by USER.  

## 8.6 Establishing a server-server connection  

The process of establishing of a server-to-server connection is fraught with danger since there are many possible areas where problems can occur - the least of which are race conditions.  

After a server has received a connection following by a PASS/SERVER pair which were recognised as being valid, the server should then reply with its own PASS/SERVER information for that connection as well as all of the other state information it knows about as described below.  

When the initiating server receives a PASS/SERVER pair, it too then checks that the server responding is authenticated properly before accepting the connection to be that server.  

### 8.6.1 Server exchange of state information when connecting  

The order of state information being exchanged between servers is essential.  The required order is as follows:  
* all known other servers;  
* all known user information;  
* all known channel information.  

Information regarding servers is sent via extra SERVER messages, user information with NICK/USER/MODE/JOIN messages and channels with MODE messages.  

NOTE: channel topics are *NOT* exchanged here because the TOPIC command overwrites any old topic information, so at best, the two sides of the connection would exchange topics.  

By passing the state information about servers first, any collisions with servers that already exist occur before nickname collisions due to a second server introducing a particular nickname.  
Due to the IRC network only being able to exist as an acyclic graph, it may be possible that the network has already reconnected in another location, the place where the collision occurs indicating where the net needs to split.  

## 8.7 Terminating server-client connections  

When a client connection closes, a QUIT message is generated on behalf of the client by the server to which the client connected.  No other message is to be generated or used.  

## 8.8 Terminating server-server connections  

If a server-server connection is closed, either via a remotely generated SQUIT or 'natural' causes, the rest of the connected IRC network must have its information updated with by the server which detected the closure.  
The server then sends a list of SQUITs (one for each server behind that connection) and a list of QUITs (again, one for each client behind that connection).  

## 8.9 Tracking nickname changes  

All IRC servers are required to keep a history of recent nickname changes.  This is required to allow the server to have a chance of keeping in touch of things when nick-change race conditions occur with commands which manipulate them.  
Commands which must trace nick changes are:  
* KILL (the nick being killed)  
* MODE (+/- o,v)  
* KICK (the nick being kicked)  

No other commands are to have nick changes checked for.  

In the above cases, the server is required to first check for the existence of the nickname, then check its history to see who that nick currently belongs to (if anyone!).  
This reduces the chances of race conditions but they can still occur with the server ending up affecting the wrong client.  
When performing a change trace for an above command it is recommended that a time range be given and entries which are too old ignored.  

For a reasonable history, a server should be able to keep previous nickname for every client it knows about if they all decided to change.  
This size is limited by other factors (such as memory, etc).  

## 8.10 Flood control of clients  

With a large network of interconnected IRC servers, it is quite easy for any single client attached to the network to supply a continuous stream of messages that result in not only flooding the network, but also degrading the level of service provided to others.  
Rather than require every 'victim' to be provide their own protection, flood protection was written into the server and is applied to all clients except services.  
The current algorithm is as follows:  
* check to see if client's `message timer' is less than current time (set to be equal if it is);  
* read any data present from the client;  
* while the timer is less than ten seconds ahead of the current time, parse any present messages and penalize the client by 2 seconds for each message;  

which in essence means that the client may send 1 message every 2 seconds without being adversely affected.  

## 8.11 Non-blocking lookups  

In a real-time environment, it is essential that a server process do as little waiting as possible so that all the clients are serviced fairly.  
Obviously this requires non-blocking IO on all network read/write operations.  
For normal server connections, this was not difficult, but there are other support operations that may cause the server to block (such as disk reads).  
Where possible, such activity should be performed with a short timeout.  

### 8.11.1 Hostname (DNS) lookups  

Using the standard resolver libraries from Berkeley and others has meant large delays in some cases where replies have timed out.  
To avoid this, a separate set of DNS routines were written which were setup for non-blocking IO operations and then polled from within the main server IO loop.  

### 8.11.2 Username (Ident) lookups  

Although there are numerous ident libraries for use and inclusion into other programs, these caused problems since they operated in a synchronous manner and resulted in frequent delays.  
Again the solution was to write a set of routines which would cooperate with the rest of the server and work using non-blocking IO.  

## 8.12 Configuration File  

To provide a flexible way of setting up and running the server, it is recommended that a configuration file be used which contains instructions to the server on the following:  
* which hosts to accept client connections from;  
* which hosts to allow to connect as servers;  
* which hosts to connect to (both actively and passively);  
* information about where the server is (university, city/state, company are examples of this);  
* who is responsible for the server and an email address at which they can be contacted;  
* hostnames and passwords for clients which wish to be given access to restricted operator commands.  

In specifying hostnames, both domain names and use of the 'dot' notation (127.0.0.1) should both be accepted.  
It must be possible to specify the password to be used/accepted for all outgoing and incoming connections (although the only outgoing connections are those to other servers).  

The above list is the minimum requirement for any server which wishes to make a connection with another server.  
Other items which may be of use are:  
* specifying which servers other server may introduce;  
* how deep a server branch is allowed to become;  
* hours during which clients may connect.  

### 8.12.1 Allowing clients to connect  

A server should use some sort of 'access control list' (either in the configuration file or elsewhere) that is read at startup and used to decide what hosts clients may use to connect to it.  

Both 'deny' and 'allow' should be implemented to provide the required flexibility for host access control.  

### 8.12.2 Operators  

The granting of operator privileges to a disruptive person can have dire consequences for the well-being of the IRC net in general due to the powers given to them.  
Thus, the acquisition of such powers should not be very easy.  The current setup requires two 'passwords' to be used although one of them is usually easy guessed.  
Storage of oper passwords in configuration files is preferable to hard coding them in and should be stored in a crypted format (ie using crypt(3) from Unix) to prevent easy theft.  

### 8.12.3 Allowing servers to connect  

The interconnection of server is not a trivial matter: a bad connection can have a large impact on the usefulness of IRC.  
Thus, each server should have a list of servers to which it may connect and which servers may connect to it.  
Under no circumstances should a server allow an arbitrary host to connect as a server.  
In addition to which servers may and may not connect, the configuration file should also store the password and other characteristics of that link.  

### 8.12.4 Administrivia  

To provide accurate and valid replies to the ADMIN command (see section 4.3.7), the server should find the relevant details in the configuration.  

## 8.13 Channel membership  

The current server allows any registered local user to join upto 10 different channels.  
There is no limit imposed on non-local users so that the server remains (reasonably) consistant with all others on a channel membership basis  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; *[to the top](#summary)*


# 9. Current problems

There are a number of recognized problems with this protocol, all of which hope to be solved sometime in the near future during its rewrite.  
Currently, work is underway to find working solutions to these problems.  

## 9.1 Scalability

It is widely recognized that this protocol does not scale sufficiently well when used in a large arena.  
The main problem comes from the requirement that all servers know about all other servers and users and that information regarding them be updated as soon as it changes.  
It is also desirable to keep the number of servers low so that the path length between any two points is kept minimal and the spanning tree as strongly branched as possible.  

## 9.2 Labels

The current IRC protocol has 3 types of labels: the nickname, the channel name and the server name.  
Each of the three types has its own domain and no duplicates are allowed inside that domain. Currently, it is possible for users to pick the label for any of the three, resulting in collisions.  
It is widely recognized that this needs reworking, with a plan for unique names for channels and nicks that don't collide being desirable as well as a solution allowing a cyclic tree.  

### 9.2.1 Nicknames

The idea of the nickname on IRC is very convenient for users to use when talking to each other outside of a channel, but there is only a finite nickname space and being what they are, its not uncommon for several people to want to use the same nick.  
If a nickname is chosen by two people using this protocol, either one will not succeed or both will removed by use of KILL (4.6.1).  

### 9.2.2 Channels

The current channel layout requires that all servers know about all channels, their inhabitants and properties.  
Besides not scaling well, the issue of privacy is also a concern.  
A collision of channels is treated as an inclusive event (both people who create the new channel are considered to be members of it) rather than an exclusive one such as used to solve nickname collisions.  

### 9.2.3 Servers

Although the number of servers is usually small relative to the number of users and channels, they two currently required to be known globally, either each one separately or hidden behind a mask.  

## 9.3 Algorithms

In some places within the server code, it has not been possible to avoid N^2 algorithms such as checking the channel list of a set of clients.  

In current server versions, there are no database consistency checks, each server assumes that a neighbouring server is correct.  
This opens the door to large problems if a connecting server is buggy or otherwise tries to introduce contradictions to the existing net.  

Currently, because of the lack of unique internal and global labels, there are a multitude of race conditions that exist.  
These race conditions generally arise from the problem of it taking time for messages to traverse and effect the IRC network.  
Even by changing to unique labels, there are problems with channel-related commands being disrupted.  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; *[to the top](#summary)*
  
  
  
  
# **RFC 2810**

First formally documented in May 1993 by RFC 1459 [IRC], the protocol has kept evolving. This documents are updates describing the current IRC protocol and the role of its different components.

The RFC 2810 specifically describes the Architecture of the IRC protocol.

# 1. RFC 2810 - Introduction

The IRC Protocol is based on the client-server model, and is well suited to running on many machines in a distributed fashion.  
A typical setup involves a single process (the server) forming a central point for clients (or other servers) to connect to, performing the required message deliver multiplexing and other functions.  

This distributed model, which requires each server to have a copy of the global state information, is still the most flagrant problem of the protocol as it is a serious handicap, which limits the maximum size a network can reach.  
If the existing networks have been able to keep growing at an incredible pace, we must thank hardware manufacturers for giving us ever more powerful systems.  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; *[to the top](#summary)*

# 2. Components

## 2.2. Clients

A client is anything connecting to a server that is not another server.  
There are two types of clients which both serve a different purpose.  

### 2.2.1. User Clients

User clients are generally programs providing a text based interface that is used to communicate interactively via IRC.  
This particular type of clients is often referred as "users".  

### 2.2.2. Service Clients

Unlike users, service clients are not intended to be used manually nor for talking.  
They have a more limited access to the chat functions of the protocol, while optionally having access to more private data from the servers.  

Services are typically automatons used to provide some kind of service (not necessarily related to IRC itself) to users.  
An example is a service collecting statistics about the origin of users connected on the IRC network.  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; *[to the top](#summary)*

# 4. IRC Protocol Services

This section describes the services offered by the IRC protocol.  
The combination of these services allow real-time conferencing.  

## 4.1. Client Locator

To be able to exchange messages, two clients must be able to locate each other.  

Upon connecting to a server, a client registers using a label which is then used by other servers and clients to know where the client is located.  
Servers are responsible for keeping track of all the labels being used.  

## 4.2. Message Relaying

The IRC protocol provides no mean for two clients to directly communicate.  
All communication between clients is relayed by the server(s).  

## 4.3. Channel Hosting And Management

A channel is a named group of one or more users which will all receive messages addressed to that channel.  
A channel is characterized by its name and current members, it also has a set of properties which can be manipulated by (some of) its members.  

Channels provide a mean for a message to be sent to several clients.  
Servers host channels, providing the necessary message multiplexing.  
Servers are also responsible for managing channels by keeping track of the channel members.  
The exact role of servers is defined in "Internet Relay Chat: Channel Management" [IRC-CHAN].  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; *[to the top](#summary)*

# 6. Current Problems

There are a number of recognized problems with this protocol, this section only addresses the problems related to the architecture of the protocol.  

## 6.1. Scalability

It is widely recognized that this protocol does not scale sufficiently well when used in a large arena.  
The main problem comes from the requirement that all servers know about all other servers, clients and channels and that information regarding them be updated as soon as it changes.  

## 6.2. Reliability

As the only network configuration allowed for IRC servers is that of a spanning tree, each link between two servers is an obvious and quite serious point of failure.  
This particular issue is addressed more in detail in "Internet Relay Chat: Server Protocol" [IRC-SERVER].  

## 6.3. Network Congestion

Another problem related to the scalability and reliability issues, as well as the spanning tree architecture, is that the protocol and architecture for IRC are extremely vulnerable to network congestions.  
This problem is endemic, and should be solved for the next generation: if congestion and high traffic volume cause a link between two servers to fail, not only this failure generates more network traffic, but the reconnection (eventually elsewhere) of two servers also generates more traffic.  

In an attempt to minimize the impact of these problems, it is strongly RECOMMENDED that servers do not automatically try to reconnect too fast, in order to avoid aggravating the situation.  

## 6.4. Privacy

Besides not scaling well, the fact that servers need to know all information about other entities, the issue of privacy is also a concern.  
This is in particular true for channels, as the related information is quite a lot more revealing than whether a user is online or not.  


###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; *[to the top](#summary)*


# Sources:
* [RFC 1459 documentation](https://tools.ietf.org/html/rfc1459)
* [RFC 2810 documentation](https://tools.ietf.org/html/rfc2810)
* [RFC 2811 documentation](https://tools.ietf.org/html/rfc2811)
* [RFC 2812 documentation](https://tools.ietf.org/html/rfc2812)
* [RFC 2813 documentation](https://tools.ietf.org/html/rfc2813)
* [RFC 7194 documentation](https://tools.ietf.org/html/rfc7194)

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; *[to the top](#summary)*
