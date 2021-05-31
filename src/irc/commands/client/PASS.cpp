#include <irc/commands/UnidentifiedCommands.hpp>

namespace NAMESPACE_IRC
{
	bool
	PassCommand::
	payload(Database& database, ABufferedConnection* const connection, argumentList const& arguments) const
	{
		if (arguments.empty())
			*connection << NeedMoreParamsError(database.hostname, name);
		else if (connection->isRegistered())
			*connection << UserAlreadyRegistred(database.hostname, connection->getUid());
		else if ((connection->authenticated = arguments.at(0) == database.password))
			return (true);
		return (false);
	}
}
