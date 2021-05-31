#include <irc/commands/ClientCommand.hpp>

namespace irc
{
	struct OperatorCommand	:	ClientCommand
	{
		OperatorCommand(std::string const& name)
			:	ClientCommand(name)
		{ }
	};
}
