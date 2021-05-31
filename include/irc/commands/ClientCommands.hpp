#pragma once

#include <irc/commands/ClientCommand.hpp>
#include <irc/commands/ChannelCommand.hpp>
#include <irc/commands/OperatorCommand.hpp>

namespace irc
{
	struct PRIVMSGCommand
		: public ClientCommand
	{
		PRIVMSGCommand()
			:	ClientCommand("PRIVMSG")
		{ }

		bool payload(Database &database, AClient *const user,
					 argumentList const &arguments) const;
	};

	struct NoticeCommand
		: public ClientCommand
	{
		NoticeCommand()
			:	ClientCommand("NOTICE")
		{ }

		bool payload(Database &database, AClient *const user,
					 argumentList const &arguments) const;
	};

	struct MotdCommand
		: public ClientCommand
	{
		MotdCommand()
			:	ClientCommand("MOTD")
		{ }

		bool payload(Database &database, AClient *const user,
					 argumentList const &arguments) const;
	};

	struct WhoQuery
		: public ClientCommand
	{
		WhoQuery()
			:	ClientCommand("WHO")
		{ }

		bool payload(Database &database, AClient *const user,
					 argumentList const &arguments) const;
	};

	struct NickCommand
		: public ClientCommand
	{
		NickCommand()
			:	ClientCommand("NICK")
		{ }

		bool payload(Database &database, AClient *const user,
					 argumentList const &arguments) const;
	};

	struct UserCommand
		: public ClientCommand
	{
		UserCommand()
			:	ClientCommand("USER")
		{ }

		bool payload(Database &database, AClient *const user,
					 argumentList const &arguments) const;
	};

	struct OperCommand
		: public ClientCommand
	{
		OperCommand()
			:	ClientCommand("OPER")
		{ }

		bool payload(Database &database, AClient *const user,
					 argumentList const &arguments) const;
	};

	struct VersionCommand
	: ClientCommand
	{
		VersionCommand()
			:	ClientCommand("VERSION")
		{ }

		bool	payload(Database& database, AClient* const user,
			argumentList const& arguments) const;
	};

	// Channel Commands
	struct JoinCommand
		: public ChannelCommand
	{
		JoinCommand()
			:	ChannelCommand("JOIN", false)
		{ }

		bool payload(Database &database, AClient *const user,
					 argumentList const &arguments) const;
	};

	struct PartCommand
		: public ChannelCommand
	{
		PartCommand()
			:	ChannelCommand("PART", true)
		{ }

		bool payload(Database &database, AClient *const user,
					 argumentList const &arguments) const;
	};

	struct ModeCommand
		: public ChannelCommand
	{
		ModeCommand()
			:	ChannelCommand("MODE", true)
		{ }

		bool payload(Database &database, AClient *const user,
					 argumentList const &arguments) const;
	};

	struct TopicCommand
		: public ChannelCommand
	{
		TopicCommand()
			:	ChannelCommand("TOPIC", true)
		{ }

		bool payload(Database &database, AClient *const user,
					 argumentList const &arguments) const;
	};

	struct NamesCommand
		: public ChannelCommand
	{
		NamesCommand()
			:	ChannelCommand("NAMES", true)
		{ }

		bool payload(Database &database, AClient *const user,
					 argumentList const &arguments) const;
	};

	struct ListCommand
		: public ChannelCommand
	{
		ListCommand()
			:	ChannelCommand("LIST", true)
		{ }

		bool payload(Database &database, AClient *const user,
					 argumentList const &arguments) const;
	};

	struct InviteCommand
		: public ChannelCommand
	{
		InviteCommand()
			:	ChannelCommand("INVITE", true)
		{ }

		bool payload(Database &database, AClient *const user,
					 argumentList const &arguments) const;
	};

	struct KickCommand
		: public ChannelCommand
	{
		KickCommand()
			:	ChannelCommand("KICK", true)
		{ }

		bool payload(Database &database, AClient *const user,
					 argumentList const &arguments) const;
	};

	// Database queries and commands

	// TODO: Users command
	/* struct UsersCommand
	: ClientCommand
	{
		UsersCommand();
		bool	payload(Database& database, AClient* const user,
			argumentList const& arguments) const;
	}; */


	struct TimeCommand
	: ClientCommand
	{
		TimeCommand()
			:	ClientCommand("TIME")
		{ }

		bool	payload(Database& database, AClient* const user,
			argumentList const& arguments) const;
	};

	struct StatsCommand
	: ClientCommand
	{
		StatsCommand()
			:	ClientCommand("STATS")
		{ }

		bool	payload(Database& database, AClient* const user,
			argumentList const& arguments) const;
	};

	struct AdminCommand
	: ClientCommand
	{
		AdminCommand()
			:	ClientCommand("ADMIN")
		{ }

		bool	payload(Database& database, AClient* const user,
			argumentList const& arguments) const;
	};
	// Operator commands

	// TODO: Check implementation of OperatorCommand
	struct RestartCommand
	: OperatorCommand
	{
		RestartCommand()
			:	OperatorCommand("RESTART")
		{ }
		bool	payload(Database& database, AClient* const user,
			argumentList const& arguments) const;
	};

	struct RehashCommand
	: OperatorCommand
	{
		RehashCommand()
			:	OperatorCommand("REHASH")
		{ }

		bool	payload(Database& database, AClient* const user,
			argumentList const& arguments) const;
	};
}
