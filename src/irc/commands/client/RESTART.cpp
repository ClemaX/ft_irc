#include <irc/commands/ClientCommands.hpp>

namespace NAMESPACE_IRC
{
	bool
	RestartCommand::
	payload(Database& database, AClient* const user, argumentList const& arguments) const
	{
		static_cast<void>(database);
		static_cast<void>(user);
		static_cast<void>(arguments);
		return (true);
	}
}
