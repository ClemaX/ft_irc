# include <irc/commands/ClientCommands.hpp>

namespace NAMESPACE_IRC
{
	bool
	OperCommand::
	payload(Database& database, AClient* const user, argumentList const& arguments) const
	{
		// NOTE: I did not handle duplicates
		//		any user knowing the good combination can be operator


		if (arguments.empty())
			*user << NeedMoreParamsError(database.hostname, name);
		//else if (std::pair<std::string, std::string>(arguments.at(0), arguments.at(1)) != database.admin.id)
		//	*user << PassMissMatchError(database.hostname);
		else
		{
			user->becomeOperator();
			*user << YoureOperReply(database.hostname);
			return (true);
		}
		return (false);
	}
}
