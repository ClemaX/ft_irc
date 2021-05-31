#include <irc/commands/ServerCommands.hpp>

namespace NAMESPACE_IRC
{
	bool
	SquitServerCommand::
	payload(Database& database, AServerConnection* const user, argumentList const& arguments) const
	{
		static_cast<void>(database);
		static_cast<void>(user);
		static_cast<void>(arguments);
		return (true);
	}
}
