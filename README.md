
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

[2. The IRC Specification - RFC 1459](#2-the-irc-specification---rfc-1459)  

[3. IRC Concepts](#3-irc-concepts)  
* [3.1 One to one comunication](#31-one-to-one-comunication)  
* [3.2 One-to-many](#32-one-to-many)  
* [3.3 One-to-all](#33-one-to-all)  

[4. Message details](#4-message-details)  

[5. OPTIONALS](#5-optionals)  

[6. REPLIES](#6-replies)  

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

[6. RFC 2810 - Current problems](#6-rfc-2810---current-problems)
* [6.1 Scalability](#61-scalability)  
* [6.2 Reliability](#62-reliability)  
* [6.3 Network Congestion](#63-network-congestion)  
* [6.4 Privacy](#64-privacy)  
  
  
  
**RFC 2811 (April 2000)**

[1. Introduction](#1-rfc-2811---introduction)  

[2. Channel Characteristics](#2-channel-characteristics)  
* [2.1 Namespace](#21-namespace)  
* [2.2 Channel Scope](#22-channel-scope)  
* [2.3 Channel Properties](#23-channel-properties)  
* [2.4 Privileged Channel Members](#24-privileged-channel-members)  

[3. Channel lifetime](#3-channel-lifetime)  
* [3.1 Standard channels](#31-standard-channels)  
* [3.2 Safe channels](#32-safe-channels)  

[4. Channel Modes](#4-channel-modes)  
* [4.1 Member Status](#41-member-status)  
* [4.2 Channel Flags](#42-channel-flags)  
* [4.3 Channel Access Control](#43-channel-access-control)  

[5. Current Implementations](#5-current-implementations)
* [5.1 Tracking Recently Used Channels](#51-tracking-recently-used-channels)
* [5.2 Safe Channels](#52-safe-channels)

[6. RFC 2811 - Current problems](#6-rfc-2811---current-problems)
* [6.1 Labels](#61-labels)
* [6.2 Mode Propagation Delays](#62-mode-propagation-delays)
* [6.3 Collisions And Channel Modes](#63-collisions-and-channel-modes)
* [6.4 Resource Exhaustion](#64-resource-exhaustion)

[7. Security Considerations](#7-security-considerations)
* [7.1 Access Control](#71-access-control)
* [7.2 Channel Privacy](#72-channel-privacy)
* [7.3 Anonymity](#73-anonymity)



**RFC 2812 (April 2000)**

[1. Introduction](#1-rfc-2812---introduction)

[2. The IRC Specification - RFC 2812](#2-the-irc-specification---rfc-2812)  
* [2.2 Character codes](#22-character-codes)  
* [2.3 Messages](#23-messages)  
* [2.4 Numeric answers](#24-numeric-answers)  
* [2.5 Wildcards expressions](#25-wildcards-expressions)  

[3. Message details](#3-message-details)  
* [3.1 Connection Registration](#31-connection-registration)  
* [3.2 Channel operations](#32-channel-operations)  
* [3.3 Sending messages](#33-sending-messages)  
* [3.4 Server queries and commands](#34-server-queries-and-commands)  
* [3.5 Service Query and Commands](#35-service-query-and-commands)  
* [3.6 User based queries](#36-user-based-queries)  
* [3.7 Miscellaneous messages](#37-miscellaneous-messages)  

[5. Replies](#5-replies)  
* [5.1 Command responses](#51-command-responses)  
* [5.2 Error Replies](#52-error-replies)  
* [5.3 Reserved numerics](#53-reserved-numerics)  

[7. RFC 2812 - Current problems](#7-rfc-2812---current-problems)
* [7.1 Nicknames](#71-nicknames)
* [7.2 Limitation of wildcards](#72-limitation-of-wildcards)
* [7.3 Security considerations](#73-security-considerations)



**RFC 2813 (April 2000)**

[1. Introduction](#1-rfc-2813---introduction)

[2. Global database](#2-global-database)
* [2.1 Servers](#21-servers)
* [2.2 Clients](#22-clients)
* [2.3 Channels](#23-channels)

[3. The IRC Server Specification](#3-the-irc-server-specification)
* [3.1 Overview](#31-overview)
* [3.2 Character codes](#32-character-codes)
* [3.3 Messages](#33-messages)
* [3.4 Numeric replies](#34-numeric-replies)

[4. Message Details](#4-message-details)
* [4.1 Connection Registration](#41-connection-registration)
* [4.2 Channel operations](#42-channel-operations)

[5. Implementation details](#5-implementation-details)

[6. Current problems](#6-current-problems)
* [6.1 Scalability](#61-scalability)
* [6.2 Labels](#62-labels)
* [6.3 Algorithms](#63-algorithms)

[7. Security Consideration](#7-security-consideration)
* [7.1 Authentication](#71-authentication)
* [7.2 Integrity](#72-integrity)


**RFC 1794 (August 2014)**


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

See section ["2. Channel Characteristics"](#2-channel-characteristics) of the RFC 2811.

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

# 2. The IRC Specification - RFC 1459

See section ["2. The IRC Specification - RFC 2812"](#2-the-irc-specification---rfc-2812) of the RFC 2812.

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

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

## 3.34One-to-all

### 3.3.1 Client to client comunication
There's any kind of unique message that can be sent to all the clients.  

### 3.3.2 Client to server comunication
Commands change the state of a channel, a user ...  
Must be sent to all the servers all over the network.  

### 3.3.3 Server to server comunication
Almost every msg sent server to server is distributed all over the network to all servers.  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

# 4. Message details

See section ["3. Message Details"](#3-message-details) of the RFC 2812.

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

# 5. OPTIONALS

This section describes OPTIONAL messages. They are not required in a working server implementation of the protocol described herein.  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

# 6. REPLIES

See section ["5. Replies"](#5-replies) of the RFC 2812.  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

# 7. Client and server authentication

Clients and servers are both subject to the same level of authentication.  

For both, an IP number to hostname lookup (and reverse check on this) is performed for all connections made to the server.  
Both connections are then subject to a password check (if there is a password set for that connection).  
These checks are possible on all connections although the password check is only commonly used with servers.  

An additional check that is becoming of more and more common is that of the username responsible for making the connection.  
Finding the username of the other end of the connection typically involves connecting to an authentication server such as IDENT as described in RFC 1413.  

Given that without passwords it is not easy to reliably determine who is on the other end of a network connection, use of passwords is strongly recommended on inter-server connections in addition to any other measures such as using an ident server.  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

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

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*


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

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*
  
  
------------------------------------------------------------
  
# **RFC 2810**

First formally documented in May 1993 by RFC 1459 [IRC], the protocol has kept evolving. This documents are updates describing the current IRC protocol and the role of its different components.

The RFC 2810 specifically describes the **Architecture** of the IRC protocol.

# 1. RFC 2810 - Introduction

The IRC Protocol is based on the client-server model, and is well suited to running on many machines in a distributed fashion.  
A typical setup involves a single process (the server) forming a central point for clients (or other servers) to connect to, performing the required message deliver multiplexing and other functions.  

This distributed model, which requires each server to have a copy of the global state information, is still the most flagrant problem of the protocol as it is a serious handicap, which limits the maximum size a network can reach.  
If the existing networks have been able to keep growing at an incredible pace, we must thank hardware manufacturers for giving us ever more powerful systems.  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

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

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

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

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

# 6. RFC 2810 - Current Problems

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


###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*
  
  
  
------------------------------------------------------------

# **RFC 2811**

First formally documented in May 1993 by RFC 1459 [IRC], the protocol has kept evolving. This documents are updates describing the current IRC protocol and the role of its different components.

The RFC 2811 specifically describes the **Channel Management** of the IRC protocol.

# 1. RFC 2811 - Introduction

One of the most notable characteristics of the IRC (Internet Relay Chat) protocol is to allow for users to be grouped in forums, called channels, providing a mean for multiple users to communicate together.  

There was originally a unique type of channels, but with the years, new types appeared either as a response to a need, or for experimental purposes.  

This document specifies how channels, their characteristics and properties are managed by IRC servers.  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*


# 2. Channel Characteristics

   A channel is a named group of one or more users which will all receive messages addressed to that channel.  
   A channel is characterized by its name, properties and current members.  

## 2.1. Namespace

Channels names :  
* Are strings.  
* Begin with '&' or '#', '+' or '!'.  
* Max length of 50 characters.
* Channel names are case insensitive  
* Can't contain spaces.  
* Can't contain ctrl^G (ASCII 7).  
* Can't contain a ','.
* A colon (':') is used as a delimiter for the channel mask.

The use of different prefixes effectively creates four (4) distinct namespaces for channel names  

## 2.2 Channel Scope

A channel entity is known by one or more servers on the IRC network.  
A user can only become member of a channel known by the server to which the user is directly connected.  
The list of servers which know of the existence of a particular channel MUST be a contiguous part of the IRC network, in order for the messages addressed to the channel to be sent to all the channel members.  

Channels with '**&**' as prefix are local to the server where they are created.  

Other channels are known to one or more servers that are connected to the network, depending on the channel mask:  
* If there is no channel mask, then the channel is known to all the servers.
* If there is a channel mask, then the channel MUST only be known to servers which has a local user on the channel, and to its neighbours if the mask matches both the local and neighbouring server names.  
Since other servers have absolutely no knowledge of the existence of such a channel, the area formed by the servers having a name matching the mask has to be contiguous for the channel to be known by all these servers.  
Channel masks are best used in conjunction with server hostmasking [IRC-SERVER].

## 2.3. Channel Properties

Each channel has its own properties, which are defined by channel modes.  
Channel modes can be manipulated by the channel members.  
The modes affect the way servers manage the channels.  

Channels with '+' as prefix do not support channel modes.  
This means that all the modes are unset, with the exception of the 't' channel flag which is set.  

## 2.4. Privileged Channel Members

In order for the channel members to keep some control over a channel, and some kind of sanity, some channel members are privileged.  
Only these members are allowed to perform the following actions on the channel:
* INVITE  - Invite a client to an invite-only channel (mode +i)
* KICK    - Eject a client from the channel
* MODE    - Change the channel's mode, as well as members' privileges
* PRIVMSG - Sending messages to the channel (mode +n, +m, +v)
* TOPIC   - Change the channel topic in a mode +t channel

### 2.4.1. Channel Operators

The channel operators (also referred to as a "chop" or "chanop") on a given channel are considered to 'own' that channel.  
Ownership of a channel is shared among channel operators.  

Channel operators are identified by the '@' symbol next to their nickname whenever it is associated with a channel (i.e., replies to the NAMES, WHO and WHOIS commands).  

Since channels starting with the character '+' as prefix do not support channel modes, no member can therefore have the status of channel operator.  

### 2.4.2. Channel Creator

A user who creates a channel with the character '!' as prefix is identified as the "channel creator".  
Upon creation of the channel, this user is also given channel operator status.  

In recognition of this status, the channel creators are endowed with the ability to toggle certain modes of the channel which channel operators may not manipulate.  

A "channel creator" can be distinguished from a channel operator by issuing the proper MODE command.  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

# 3. Channel lifetime

In regard to the lifetime of a channel, there are typically two groups of channels:  
* standard channels which prefix is either '&', '#' or '+'
* "safe channels" which prefix is '!'

## 3.1. Standard channels

These channels are created implicitly when the first user joins it, and cease to exist when the last user leaves it.  
While the channel exists, any client can reference the channel using the name of the channel.  

The user creating a channel automatically becomes channel operator with the notable exception of channels which name is prefixed by the character '+'.  

In order to avoid the creation of duplicate channels (typically when the IRC network becomes disjoint because of a split between two servers), channel names SHOULD NOT be allowed to be reused by a user if a [channel operator](#241-channel-operators) has recently left the channel because of a network split.  
If this happens, the channel name is temporarily unavailable.  
The duration while a channel remains unavailable should be tuned on a per IRC network basis.  
It is important to note that this prevents local users from creating a channel using the same name, but does not prevent the channel to be recreated by a remote user. The latter typically happens when the IRC network rejoins.  
Obviously, this mechanism only makes sense for channels which name begins with the character '#', but MAY be used for channels which name begins with the character '+'.  
This mechanism is commonly known as "Channel Delay".  

## 3.2 Safe Channels
Unlike other channels, "safe channels" are not implicitly created.  
A user wishing to create such a channel MUST request the creation by sending a special JOIN command to the server in which the channel identifier (then unknown) is replaced by the character '!'.  
The creation process for this type of channel is strictly controlled.  
The user only chooses part of the channel name (known as the channel "short name"), the server automatically prepends the user provided name with a channel identifier consisting of five (5) characters.  
The channel name resulting from the combination of these two elements is unique, making the channel safe from abuses based on network splits.  

The user who creates such a channel automatically becomes "[channel creator](#242-channel-creator)".   

A server MUST NOT allow the creation of a new channel if another channel with the same short name exists; or if another channel with the same short name existed recently AND any of its member(s) left because of a network split.  
Such channel ceases to exist after last user leaves AND no other member recently left the channel because of a network split.  

Unlike the mechanism described in section 5.2.2 (Channel Delay), in this case, channel names do not become unavailable: these channels may continue to exist after the last user left.  
Only the user creating the channel becomes "channel creator", users joining an existing empty channel do not automatically become "channel creator" nor "channel operator".  

To ensure the uniqueness of the channel names, the channel identifier created by the server MUST follow specific rules.  For more details on this, see section 5.2.1 (Channel Identifier).  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*


# 4. Channel Modes

The various modes available for channels are as follows:  
* O - give "channel creator" status;
* o - give/take channel operator privilege;
* v - give/take the voice privilege;

* a - toggle the anonymous channel flag;
* i - toggle the invite-only channel flag;
* m - toggle the moderated channel;
* n - toggle the no messages to channel from clients on the outside;
* q - toggle the quiet channel flag;
* p - toggle the private channel flag;
* s - toggle the secret channel flag;
* r - toggle the server reop channel flag;
* t - toggle the topic settable by channel operator only flag;

* k - set/remove the channel key (password);
* l - set/remove the user limit to channel;

* b - set/remove ban mask to keep users out;
* e - set/remove an exception mask to override a ban mask;
* I - set/remove an invitation mask to automatically override the invite-only flag;

Unless mentioned otherwise below, all these modes can be manipulated by "channel operators" by using the MODE command defined in "IRC Client Protocol" [IRC-CLIENT].  

## 4.1 Member Status

The modes in this category take a channel member nickname as argument and affect the privileges given to this user.

### 4.1.1 "Channel Creator" Status

The mode 'O' is only used in conjunction with "safe channels" and SHALL NOT be manipulated by users.  
Servers use it to give the user creating the channel the status of "channel creator".  

### 4.1.2 Channel Operator Status

The mode 'o' is used to toggle the operator status of a channel member.  

### 4.1.3 Voice Privilege

The mode 'v' is used to give and take voice privilege to/from a channel member.  
Users with this privilege can talk on moderated channels.  

## 4.2 Channel Flags

The modes in this category are used to define properties which affects how channels operate.  

### 4.2.1 Anonymous Flag

The channel flag 'a' defines an anonymous channel.  
This means that when a message sent to the channel is sent by the server to users, and the origin is a user, then it MUST be masked.  
To mask the message, the origin is changed to "anonymous!anonymous@anonymous." (e.g., a user with the nickname "anonymous", the username "anonymous" and from a host called "anonymous.").  
Because of this, servers MUST forbid users from using the nickname "anonymous".  
Servers MUST also NOT send QUIT messages for users leaving such channels to the other channel members but generate a PART message instead.  

On channels with the character '&' as prefix, this flag MAY be toggled by channel operators, but on channels with the character '!' as prefix, this flag can be set (but SHALL NOT be unset) by the "channel creator" only.  
This flag MUST NOT be made available on other types of channels.  

Replies to the WHOIS, WHO and NAMES commands MUST NOT reveal the presence of other users on channels for which the anonymous flag is set.  

### 4.2.2 Invite Only Flag

When the channel flag 'i' is set, new members are only accepted if their mask matches Invite-list (See section 4.3.2) or they have been invited by a channel operator.  
This flag also restricts the usage of the INVITE command to channel operators.  


### 4.2.3 Moderated Channel Flag

The channel flag 'm' is used to control who may speak on a channel.  
When it is set, only channel operators, and members who have been given the voice privilege may send messages to the channel.

This flag only affects users.  

### 4.2.4 No Messages To Channel From Clients On The Outside

When the channel flag 'n' is set, only channel members MAY send messages to the channel.  

This flag only affects users.  

### 4.2.5 Quiet Channel

The channel flag 'q' is for use by servers only.  
When set, it restricts the type of data sent to users about the channel operations: other user joins, parts and nick changes are not sent.  
From a user's point of view, the channel contains only one user.  

This is typically used to create special local channels on which the server sends notices related to its operations.  
This was used as a more efficient and flexible way to replace the user mode 's' defined in RFC 1459.  

### 4.2.6 Private and Secret Channels

The channel flag 'p' is used to mark a channel "private" and the channel flag 's' to mark a channel "secret".  
Both properties are similar and conceal the existence of the channel from other users.  

This means that there is no way of getting this channel's name from the server without being a member.  
In other words, these channels MUST be omitted from replies to queries like the WHOIS command.  

When a channel is "secret", in addition to the restriction above, the server will act as if the channel does not exist for queries like the TOPIC, LIST, NAMES commands.  
Note that there is one exception to this rule: servers will correctly reply to the MODE command.  
Finally, secret channels are not accounted for in the reply to the LUSERS command when the \<mask\> parameter is specified.  

The channel flags 'p' and 's' MUST NOT both be set at the same time.  
If a MODE message originating from a server sets the flag 'p' and the flag 's' is already set for the channel, the change is silently ignored.  
This should only happen during a split healing phase.  

### 4.2.7 Server Reop Flag

The channel flag 'r' is only available on channels which name begins with the character '!' and MAY only be toggled by the "channel creator".  

This flag is used to prevent a channel from having no channel operator for an extended period of time.  
When this flag is set, any channel that has lost all its channel operators for longer than the "reop delay" period triggers a mechanism in servers to reop some or all of the channel inhabitants.  
This mechanism is described more in detail in section 5.2.4 (Channel Reop Mechanism).  

### 4.2.8 Topic

The channel flag 't' is used to restrict the usage of the TOPIC command to channel operators.  

### 4.2.9 User Limit

A user limit may be set on channels by using the channel flag 'l'.
When the limit is reached, servers MUST forbid their local users to join the channel.  

The value of the limit MUST only be made available to the channel members in the reply sent by the server to a MODE query.  

### 4.2.10 Channel Key

When a channel key is set (by using the mode 'k'), servers MUST reject their local users request to join the channel unless this key is given.  

The channel key MUST only be made visible to the channel members in the reply sent by the server to a MODE query.  

## 4.3 Channel Access Control

The last category of modes is used to control access to the channel, they take a mask as argument.  

In order to reduce the size of the global database for control access modes set for channels, servers MAY put a maximum limit on the number of such modes set for a particular channel.  
If such restriction is imposed, it MUST only affect user requests.  
The limit SHOULD be homogeneous on a per IRC network basis.  

### 4.3.1 Channel Ban and Exception

When a user requests to join a channel, his local server checks if the user's address matches any of the ban masks set for the channel.  
If a match is found, the user request is denied unless the address also matches an exception mask set for the channel.  

Servers MUST NOT allow a channel member who is banned from the channel to speak on the channel, unless this member is a channel operator or has voice privilege.  

A user who is banned from a channel and who carries an invitation sent by a channel operator is allowed to join the channel.  

### 4.3.2 Channel Invitation

For channels which have the invite-only flag set, users whose address matches an invitation mask set for the channel are allowed to join the channel without any invitation.  


###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

# 5. Current Implementations

The only current implementation of these rules as part of the IRC protocol is the IRC server, version 2.10.  

## 5.1 Tracking Recently Used Channels

This mechanism is commonly known as "Channel Delay" and generally only applies to channels which names is prefixed with the character '#'.  

When a network split occurs, servers SHOULD keep track of which channels lost a "channel operator" as the result of the break.  
These channels are then in a special state which lasts for a certain period of time.  
In this particular state, the channels cannot cease to exist.  
If all the channel members leave the channel, the channel becomes unavailable: the server local clients cannot join the channel as long as it is empty.  

Once a channel is unavailable, it will become available again either because a remote user has joined the channel (most likely because the network is healing), or because the delay period has expired (in which case the channel ceases to exist and may be re-created).  

The duration for which a channel death is delayed SHOULD be set considering many factors among which are the size (user wise) of the IRC network, and the usual duration of network splits.  
It SHOULD be uniform on all servers for a given IRC network.  

## 5.2 Safe Channels

This document introduces the notion of "safe channels".  
These channels have a name prefixed with the character '!' and great effort is made to avoid collisions in this name space.  
Collisions are not impossible, however they are very unlikely.

For more information about the different cases and solution concerning this section, have a look at the [RFC 2811 documentation](https://tools.ietf.org/html/rfc2811), section 5.2.

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

# 6. RFC 2811 - Current problems

There are a number of recognized problems with the way IRC channels are managed.  
Some of these can be directly attributed to the rules defined in this document, while others are the result of the underlying "IRC Server Protocol" [IRC-SERVER].  
Although derived from RFC 1459, this document introduces several novelties in an attempt to solve some of the known problems.  

You will find below the summary of the current problem concerning channels.
For more information about this problems, have a look at the [RFC 2811 documentation](https://tools.ietf.org/html/rfc2811), section 6.

## 6.1 Labels

### 6.1.1 Channel Delay

### 6.1.2 Safe Channels

## 6.2 Mode Propagation Delays

## 6.3 Collisions And Channel Modes

## 6.4 Resource Exhaustion

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

# 7. Security Considerations

## 7.1 Access Control

One of the main ways to control access to a channel is to use masks which are based on the username and hostname of the user connections.  
This mechanism can only be efficient and safe if the IRC servers have an accurate way of authenticating user connections, and if users cannot easily get around it.  
While it is in theory possible to implement such a strict authentication mechanism, most IRC networks (especially public networks) do not have anything like this in place and provide little guaranty about the accuracy of the username and hostname for a particular client connection.  

Another way to control access is to use a channel key, but since this key is sent in plaintext, it is vulnerable to traditional man in the middle attacks.  

## 7.2 Channel Privacy

Because channel collisions are treated as inclusive events (See Section 6.3), it is possible for users to join a channel overriding its access control settings.  
This method has long been used by individuals to "take over" channels by "illegitimately" gaining channel operator status on the channel.  
The same method can be used to find out the exact list of members of a channel, as well as to eventually receive some of the messages sent to the channel.  

## 7.3 Anonymity

The anonymous channel flag (See Section 4.2.1) can be used to render all users on such channel "anonymous" by presenting all messages to the channel as originating from a pseudo user which nickname is "anonymous".  
This is done at the client-server level, and no anonymity is provided at the server-server level.  

It should be obvious to readers, that the level of anonymity offered is quite poor and insecure, and that clients SHOULD display strong warnings for users joining such channels.  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*



# **RFC 2812**

First formally documented in May 1993 by RFC 1459 [IRC], the protocol has kept evolving. This documents are updates describing the current IRC protocol and the role of its different components.

The RFC 2812 specifically describes the **Client Protocol** of the IRC protocol.

# 1. RFC 2812 - Introduction

The IRC (Internet Relay Chat) protocol is for use with text based conferencing; the simplest client being any socket program capable of connecting to the server.  

This document defines the Client Protocol, and assumes that the reader is familiar with the IRC Architecture.  

# 2. The IRC Specification - RFC 2812

See section ["2. The IRC Specification - RFC 2812"](#2-the-irc-specification---rfc-2812) of the RFC 2812.

## 2.2 Character codes
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
Section 5 contains the numeric answers codes list.  

## 2.5 Wildcards expressions

When wildcards are allowed in a string, it is referred as a "mask".  

For string matching purposes, the protocol allows the use of two special characters:
* '?' (%x3F) to match one and only one character
* '\*' (%x2A) to match any number of any characters

These two characters can be escaped using the character '\' (%x5C).  

The Augmented BNF syntax for this is:  
mask       =  *( nowild / noesc wildone / noesc wildmany )  
wildone    =  %x3F  
wildmany   =  %x2A  
nowild     =  %x01-29 / %x2B-3E / %x40-FF  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; any octet except NUL, "*", "?"  
noesc      =  %x01-5B / %x5D-FF  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; any octet except NUL and "\"  
matchone   =  %x01-FF  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; matches wildone  
matchmany  =  *matchone  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; matches wildmany  

Examples:
&nbsp; &nbsp; \- *a?c*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Matches any string of 3 characters in length starting with "a" and ending with "c"  
&nbsp; &nbsp; \- *a\*c*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Matches any string of at least 2 characters in length starting with "a" and ending with "c"  


# 3. Message Details

## 3.1 Connection Registration

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


## 3.2 Channel operations

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



## 3.3 Sending messages

The main purpose of the IRC protocol is to provide a base for clients to communicate with each other.  

PRIVMSG and NOTICE are the only messages available which actually perform delivery of a text message from one client to another - the rest just make it possible and try to ensure it happens in a reliable and structured manner.  

### 3.3.1 Private messages

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

### 3.3.2 Notice

Command: **NOTICE**  
   Parameters: \<nickname\> \<text\>  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

## 3.4 Server queries and commands

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

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

## 3.5 Service Query and Commands

The service query group of commands has been designed to return information about any service which is connected to the network.  

Command: **SERVLIST**  
   Parameters: [ \<mask\> [ \<type\> ] ]  

The SERVLIST command is used to list services currently connected to the network and visible to the user issuing the command.  
The optional parameters may be used to restrict the result of the query (to matching services names, and services type).  
 
Numeric Replies:  
&nbsp; &nbsp; RPL_SERVLIST &nbsp; &nbsp; &nbsp; &nbsp;  RPL_SERVLISTEND  


Command: **SQUERY**
   Parameters: \<servicename\> \<text\>
   Examples:  
&nbsp; &nbsp; \- *SQUERY irchelp :HELP privmsg*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Message to the service with nickname irchelp.  
&nbsp; &nbsp; \- *SQUERY dict@irc.fr :fr2en blaireau*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Message to the service with name dict@irc.fr.  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

## 3.6 User based queries

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

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

## 3.7 Miscellaneous messages

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

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

# 5. Replies

## 5.1 Command responses

Numerics in the range from 001 to 099 are used for client-server connections only and should never travel between servers.  
Replies generated in the response to commands are found in the range from 200 to 399.

001 &nbsp; &nbsp; RPL_WELCOME  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "Welcome to the Internet Relay Network \<nick\>!\<user\>@\<host\>"  
002 &nbsp; &nbsp; RPL_YOURHOST  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "Your host is \<servername\>, running version \<ver\>"  
003 &nbsp; &nbsp; RPL_CREATED  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "This server was created \<date\>"  
004 &nbsp; &nbsp; RPL_MYINFO  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "\<servername\> \<version\> \<available user modes\> \<available channel modes\>"  
005 &nbsp; &nbsp; RPL_BOUNCE  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; "Try server \<server name\>, port \<port number\>"  

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


## 5.2 Error Replies

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


## 5.3 Reserved numerics

These numerics are not described above since they fall into one of the following categories:  
&nbsp; &nbsp; &nbsp; &nbsp; 1\. no longer in use;  
&nbsp; &nbsp; &nbsp; &nbsp; 2\. reserved for future planned use;  
&nbsp; &nbsp; &nbsp; &nbsp; 3\. in current use but are part of a non-generic 'feature' of the current IRC server.  

        209     RPL_TRACECLASS
        234     RPL_SERVLIST
        235     RPL_SERVLISTEND
        361     RPL_KILLDONE
        
        466     ERR_YOUWILLBEBANNED     476     ERR_BADCHANMASK

        231    RPL_SERVICEINFO     232  RPL_ENDOFSERVICES
        233    RPL_SERVICE
        300    RPL_NONE            316  RPL_WHOISCHANOP
        361    RPL_KILLDONE        362  RPL_CLOSING
        363    RPL_CLOSEEND        373  RPL_INFOSTART
        384    RPL_MYPORTIS

        213    RPL_STATSCLINE      214  RPL_STATSNLINE
        215    RPL_STATSILINE      216  RPL_STATSKLINE
        217    RPL_STATSQLINE      218  RPL_STATSYLINE
        240    RPL_STATSVLINE      241  RPL_STATSLLINE
        244    RPL_STATSHLINE      244  RPL_STATSSLINE
        246    RPL_STATSPING       247  RPL_STATSBLINE
        250    RPL_STATSDLINE
        492    ERR_NOSERVICEHOST


###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*


# 7. RFC 2812 - Current problems

The IRC software, version 2.10 is the only complete implementation of the IRC protocol (client and server).  
Because of the small amount of changes in the client protocol since the publication of RFC 1459, implementations that follow it are likely to be compliant with this protocol or to require a small amount of changes to reach compliance.  

You will find below the summary of the current problem concerning clients protocol.  
For more information about this problems, have a look at the [RFC 2812 documentation](https://tools.ietf.org/html/rfc2812), section 7.  

## 7.1 Nicknames

## 7.2 Limitation of wildcards

## 7.3 Security considerations


###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*


# **RFC 2813**

First formally documented in May 1993 by RFC 1459 [IRC], the protocol has kept evolving. This documents are updates describing the current IRC protocol and the role of its different components.

The RFC 2813 specifically describes the **Server Protocol** of the IRC protocol.

# 1. RFC 2813 - Introduction

This document is intended for people working on implementing an IRC server but will also be useful to anyone implementing an IRC service.  

Servers provide the three basic services required for realtime conferencing defined by the "Internet Relay Chat: Architecture" : client locator (via the client protocol ), message relaying (via the server protocol defined in this document) and channel hosting and management (following specific rules [IRC- CHAN]).  


###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

# 2. Global database

Although the IRC Protocol defines a fairly distributed model, each server maintains a "global state database" about the whole IRC network.  
This database is, in theory, identical on all servers.

## 2.1 Servers

Servers are uniquely identified by their name which has a maximum length of sixty three (63) characters.  
See the protocol grammar rules (section 3.3.1) for what may and may not be used in a server name.  

Each server is typically known by all other servers, however it is possible to define a "hostmask" to group servers together according to their name.  
Inside the hostmasked area, all the servers have a name which matches the hostmask, and any other server with a name matching the hostmask SHALL NOT be connected to the IRC network outside the hostmasked area.  
Servers which are outside the area have no knowledge of the individual servers present inside the area, instead they are presented with a virtual server which has the hostmask for name.  


## 2.2 Clients

For each client, all servers MUST have the following information:  
* a netwide unique identifier (whose format depends on the type of client)
* the server to which the client is connected.  

### 2.2.1 Users

Each user is distinguished from other users by a unique nickname having a maximum length of nine (9) characters.  
In addition to the nickname, all servers MUST have the following information about all users:  
* the name of the host that the user is running on
* the username of the user on that host
* the server to which the client is connected.  

### 2.2.2 Services

Each service is distinguished from other services by a service name composed of a nickname and a server name.  
The nickname has a maximum length of nine (9) characters.  
The server name used to compose the service name is the name of the server to which the service is connected.  
In addition to this service name all servers MUST know the service type.  

Services differ from users by the format of their identifier, but more importantly services and users don't have the same type of access to the server: services can request part or all of the global state information that a server maintains, but have a more restricted set of commands available to them and are not allowed to join channels.  
Finally services are not usually subject to the "Flood control" mechanism described in section 5.8.

## 2.3 Channels
 
Alike services, channels have a scope and are not necessarily known to all servers.  When a channel existence is known to a server, the server MUST keep track of the channel members, as well as the channel modes.

# 3. The IRC Server Specification

## 3.1 Overview

The protocol as described herein is for use with server to server connections.  
For client to server connections, see the IRC Client Protocol specification IN [RFC 2812 documentation](https://tools.ietf.org/html/rfc2812).  

There are, however, more restrictions on client connections (which are considered to be untrustworthy) than on server connections.   

## 3.2 Character codes

See section [2.2 Character codes](#22-character-codes) in RFC 2812.

## 3.3 Messages

Servers and clients send each other messages which may or may not generate a reply.  
Most communication between servers do not generate any reply, as servers mostly perform routing tasks for the clients.  
 
Each IRC message may consist of up to three main parts: the prefix (OPTIONAL), the command, and the command parameters (maximum of fifteen (15)).  
The prefix, command, and all parameters are separated by one ASCII space character (0x20) each.   

The presence of a prefix is indicated with a single leading ASCII colon character (':', 0x3b), which MUST be the first character of the message itself.  There MUST be NO gap (whitespace) between the colon and the prefix.  
The prefix is used by servers to indicate the true origin of the message.  
If the prefix is missing from the message, it is assumed to have originated from the connection from which it was received.  
Clients SHOULD not use a prefix when sending a message from themselves; if they use one, the only valid prefix is the registered nickname associated with the client.   

When a server receives a message, it MUST identify its source using the (eventually assumed) prefix.  
If the prefix cannot be found in the server's internal database, it MUST be discarded, and if the prefix indicates the message comes from an (unknown) server, the link from which the message was received MUST be dropped.  
Dropping a link in such circumstances is a little excessive but necessary to maintain the integrity of the network and to prevent future problems.  
Another common error condition is that the prefix found in the server's internal database identifies a different source (typically a source registered from a different link than from which the message arrived).  
If the message was received from a server link and the prefix identifies a client, a KILL message MUST be issued for the client and sent to all servers.  
In other cases, the link from which the message arrived SHOULD be dropped for clients, and MUST be dropped for servers.  
In all cases, the message MUST be discarded.  

The command MUST either be a valid IRC command or a three (3) digit number represented in ASCII text.  

IRC messages are always lines of characters terminated with a CR-LF (Carriage Return - Line Feed) pair, and these messages SHALL NOT exceed 512 characters in length, counting all characters including the trailing CR-LF.  
Thus, there are 510 characters maximum allowed for the command and its parameters.  There is no provision for continuation message lines.  

### 3.3.1 Message format in Augmented BNF

The protocol messages must be extracted from the contiguous stream of octets.  
The current solution is to designate two characters, CR and LF, as message separators.  
Empty messages are silently ignored, which permits use of the sequence CR-LF between messages without extra problems.  

The extracted message is parsed into the components \<prefix\>, \<command\> and list of parameters (\<params\>).  

The Augmented BNF representation for this is found in "IRC Client Protocol".  

The extended prefix (["!" user "@" host ]) MUST NOT be used in server to server communications and is only intended for server to client messages in order to provide clients with more useful information about who a message is from without the need for additional queries.  

## 3.4 Numeric replies

See section [2.4 Numeric replies](#24-numeric-replies) in RFC 2812.

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*


# 4. Message Details

All the messages recognized by the IRC server and client are described in the IRC Client Protocol specification.  
Where the reply ERR_NOSUCHSERVER is returned, it means that the target of the message could not be found.  
The server MUST NOT send any other replies after this error for that command.  
The server to which a client is connected is required to parse the complete message, returning any appropriate errors.  

If the server encounters a fatal error while parsing a message, an error MUST be sent back to the client and the parsing terminated.  
A fatal error may follow from incorrect command, a destination which is otherwise unknown to the server (server, client or channel names fit this category), not enough parameters or incorrect privileges.  

If a full set of parameters is presented, then each MUST be checked for validity and appropriate responses sent back to the client.  
In the case of messages which use parameter lists using the comma as an item separator, a reply MUST be sent for each item.  

In the examples below, some messages appear using the full format:  
  :Name COMMAND parameter list

Such examples represent a message from "Name" in transit between servers, where it is essential to include the name of the original sender of the message so remote servers may send back a reply along the correct path.  

The message details for client to server communication are described in the "IRC Client Protocol".  
Some sections in the following pages apply to some of these messages, they are additions to the message specifications which are only relevant to server to server communication, or to the server implementation.  
The messages which are introduced here are only used for server to server communication.  

## 4.1 Connection Registration

The commands described here are used to register a connection with another IRC server.  

For more details about a specific commande, check the [RFC 2813 documentation](https://tools.ietf.org/html/rfc2813), section 4.  

### 4.1.1 Password message

Command: **PASS**  
   Parameters: \<password\> \<version\> \<flags\> [\<options\>]  
   Numeric Replies:  
           ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED
   Example:  
&nbsp; &nbsp; \- *PASS moresecretpassword 0210010000 IRC|aBgH$ Z*  

### 4.1.2 Server message

Command: **SERVER**  
   Parameters: \<servername\> \<hopcount\> \<token\> \<info\>  
   Numeric Replies:  
           ERR_ALREADYREGISTRED  
   Example:  
&nbsp; &nbsp; \- *SERVER test.oulu.fi 1 1 :Experimental server*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; New server test.oulu.fi introducing itself and attempting to register.  
&nbsp; &nbsp; \- *:tolsun.oulu.fi SERVER csd.bu.edu 5 34 :BU Central Server*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Server tolsun.oulu.fi is our uplink for csd.bu.edu which is 5 hops away.  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;   The token "34" will be used by tolsun.oulu.fi when introducing new users or services connected to csd.bu.edu.  

### 4.1.3 Nick

Command: **NICK**  
   Parameters: \<nickname\> \<hopcount\> \<username\> \<host\> \<servertoken\> \<umode\> \<realname\>  
   Examples:  
&nbsp; &nbsp; \- *NICK syrk 5 kalt millennium.stealth.net 34 +i :Christophe Kalt*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; New user with nickname "syrk", username "kalt", connected from host   "millennium.stealth.net" to server "34" ("csd.bu.edu" according to the previous example).  
&nbsp; &nbsp; \- *:krys NICK syrk*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; The other form of the NICK message, as defined in "IRC Client Protocol" and used between servers: krys changed his nickname to syrk  

### 4.1.4 Service message

Command: **SERVICE**  
   Parameters: \<servicename\> \<servertoken\> \<distribution\> \<type\> \<hopcount\> \<info\>  
   Numeric Replies:  
           ERR_ALREADYREGISTRED            ERR_NEEDMOREPARAMS  
           ERR_ERRONEUSNICKNAME  
           RPL_YOURESERVICE                RPL_YOURHOST  
           RPL_MYINFO  
   Example:  
&nbsp; &nbsp; \- *SERVICE dict@irc.fr 9 *.fr 0 1 :French Dictionary *  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; r" registered on server "9" is being announced to another server.  This service will only be available on servers whose name matches "*.fr".  

### 4.1.5 Quit

Command: **QUIT**  
   Parameters: [\<Quit Message\>]  
   Numeric Replies:  
           None.  
   Examples:  
&nbsp; &nbsp; \- *:WiZ QUIT :Gone to have lunch*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; Preferred message format.  

### 4.1.6 Server quit message

Command: **SQUIT**  
   Parameters: \<server\> \<comment\>  
   Numeric replies:  
           ERR_NOPRIVILEGES                ERR_NOSUCHSERVER  
           ERR_NEEDMOREPARAMS  
   Example:  
&nbsp; &nbsp; \- *SQUIT tolsun.oulu.fi :Bad Link ?*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; the server link tolson.oulu.fi has been terminated because of "Bad Link".  
&nbsp; &nbsp; \- *:Trillian SQUIT cm22.eng.umd.edu :Server out of control*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; message from Trillian to disconnect "cm22.eng.umd.edu" from the net because "Server out of control".  

## 4.2 Channel operations

This group of messages is concerned with manipulating channels, their properties (channel modes), and their contents (typically users).  
In implementing these, a number of race conditions are inevitable when users at opposing ends of a network send commands which will ultimately clash.  
It is also REQUIRED that servers keep a nickname history to ensure that wherever a \<nick\> parameter is given, the server check its history in case it has recently been changed.  

### 4.2.1 Join message

Command: **JOIN**  
   Parameters: \<channel\>[ %x7 \<modes\> ] \*( "," \<channel\>[ %x7 \<modes\> ] )
   Numeric Replies:  
           ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN  
           ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY  
           ERR_CHANNELISFULL               ERR_BADCHANMASK  
           ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS  
           ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE  
           RPL_TOPIC
   Examples:  
&nbsp; &nbsp; \- *:WiZ JOIN #Twilight_zone*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ; JOIN message from WiZ  

### 4.2.2 Njoin message

Command: **NJOIN**  
   Parameters: \<channel\> [ "@@" / "@" ] [ "+" ] \<nickname\> \*( "," [ "@@" / "@" ] [ "+" ] \<nickname\> )
   Numeric Replies:  
           ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL  
           ERR_ALREADYREGISTRED  
   Examples:  
&nbsp; &nbsp; \- *:ircd.stealth.net NJOIN #Twilight_zone :@WiZ,+syrk,avalon*  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ;NJOIN message from ircd.stealth.net announcing users joining the Twilight_zone channel: WiZ with channel operator status, syrk with voice privilege and avalon with no privilege.  


### 4.2.3 Mode message

The MODE message is a dual-purpose command in IRC.  
It allows both usernames and channels to have their mode changed.  

When parsing MODE messages, it is RECOMMENDED that the entire message be parsed first, and then the changes which resulted passed on.  

It is REQUIRED that servers are able to change channel modes so that "channel creator" and "channel operators" may be created.  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*


# 5. Implementation details

See [RFC 2813 documentation](https://tools.ietf.org/html/rfc2813), section 5.  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*

# 6. Current problems

You will find below the summary of the current problem concerning clients protocol.  
For more information about this problems, have a look at the [RFC 2813 documentation](https://tools.ietf.org/html/rfc2813), section 6.  

## 6.1 Scalability

## 6.2 Labels

### 6.2.1 Nicknames

### 6.2.2 Channels

### 6.2.3 Servers

## 6.3 Algorithms

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*


# 7. Security Consideration

## 7.1 Authentication

Servers only have two means of authenticating incoming connections: plain text password, and DNS lookups.  
While these methods are weak and widely recognized as unsafe, their combination has proven to be sufficient in the past:  
 * public networks typically allow user connections with only few restrictions, without requiring accurate authentication.
 * private networks which operate in a controlled environment often use home-grown authentication mechanisms not available on the internet: reliable ident servers, or other proprietary mechanisms.  

The same comments apply to the authentication of IRC Operators.  

It should also be noted that while there has been no real demand over the years for stronger authentication, and no real effort to provide better means to safely authenticate users, the current protocol offers enough to be able to easily plug-in external authentication methods based on the information that a client can submit to the server upon connection: nickname, username, password.  

## 7.2 Integrity

Since the PASS and OPER messages of the IRC protocol are sent in clear text, a stream layer encryption mechanism (like "The TLS Protocol") could be used to protect these transactions.  

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*



# **RFC 7194**

This document describes the commonly accepted practice of listening on TCP port 6697 for incoming Internet Relay Chat (IRC) connections encrypted via TLS/SSL.  

The RFC 2813 specifically describes the **Default Port for Internet Relay Chat (IRC) via TLS/SSL** of the IRC protocol.  

See [RFC 7194 documentation](https://tools.ietf.org/html/rfc7194) for information.  


# Sources:
* [RFC 1459 documentation](https://tools.ietf.org/html/rfc1459)
* [RFC 2810 documentation](https://tools.ietf.org/html/rfc2810)
* [RFC 2811 documentation](https://tools.ietf.org/html/rfc2811)
* [RFC 2812 documentation](https://tools.ietf.org/html/rfc2812)
* [RFC 2813 documentation](https://tools.ietf.org/html/rfc2813)
* [RFC 7194 documentation](https://tools.ietf.org/html/rfc7194)

###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  *[to the top](#summary)*
