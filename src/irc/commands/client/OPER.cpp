# include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	bool
	Server::OperCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		// NOTE: I did not handle duplicates
		//		any user knowing the good combination can be operator


		if (arguments.size() > 1)
		{
			// TO DO: if is this host handles operators

			// Missmatches with server admin data
			if (std::pair<std::string, std::string>(arguments.at(0),
			arguments.at(1)) != server.admin.id)
			{
				*user << PassMissMatchError(server.hostname);
				goto error;
			}

			user->becomeOperator();
			*user << YoureOperReply(server.hostname);
			return (true);
		}
		*user << NeedMoreParamsError(server.hostname, name);
		error:
		return (false);
	}
}
