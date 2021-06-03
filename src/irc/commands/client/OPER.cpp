# include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	void
	Server::OperCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		// NOTE: I did not handle duplicates
		//		any user knowing the good combination can be operator


		if (arguments.size() < 2)
			*user << NeedMoreParamsError(server.hostname, name);
		else
		{
			// TODO: if is this host handles operators

			if (std::pair<std::string, std::string>(arguments.at(0),
			arguments.at(1)) != server.admin.id) // Missmatches with server admin data
				*user << PassMissMatchError(server.hostname);
			else
			{
				user->becomeOperator();
				*user << YoureOperReply(server.hostname);
			}
		}
	}
}
