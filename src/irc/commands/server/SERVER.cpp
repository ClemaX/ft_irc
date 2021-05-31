# include <irc/commands/UnidentifiedCommands.hpp>

namespace NAMESPACE_IRC
{
	bool
	ServerServerCommand::
	payload(Database& database, ABufferedConnection* const user, argumentList const& arguments) const
	{
		static_cast<void>(database);
		static_cast<void>(user);
		static_cast<void>(arguments);
		return (true);
	}
}
