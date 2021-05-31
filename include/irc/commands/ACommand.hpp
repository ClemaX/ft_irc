#pragma once

#include <vector>
#include <string>

#include <irc/Database.hpp>

namespace irc
{
	//class Database;

	typedef std::vector<std::string>	argumentList;

	template<typename Connection>
	struct ACommand
	{
	public:
		std::string const					name;

		~ACommand()
		{ };

		virtual bool	execute(Database& database, Connection* const connection,
			argumentList const& arguments) const throw()
			{ return payload(database, connection, arguments); };

		virtual bool	payload(Database& database, Connection* const connection,
			argumentList const& arguments) const = 0;

	protected:

		ACommand()
		{ };

		ACommand(std::string const& name)
			:	name(name)
		{ }
	};

	template<typename _Cmd>
	_Cmd const*	parseCommand(
		_Cmd const*const* commands,
		size_t commandCount,
		std::string::const_iterator& it,
		std::string::const_iterator& last
	);
}
