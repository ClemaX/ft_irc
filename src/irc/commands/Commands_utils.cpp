#include <irc/Server.hpp>


namespace irc
{

	void	parseArgumentsQueue(std::string const &argument, std::queue<std::string> &argQueue)
	{
		std::string::const_iterator	it;
		std::string::const_iterator	end;
		std::string::const_iterator	fieldLast;
		std::string	temp;
		
		it = argument.begin();
		end = argument.end();
		while (it != end)
		{
			fieldLast =	std::find(it, end, IRC_MESSAGE_ARGUMENT_LIST_DELIM);
			temp.assign(it, fieldLast);
			if (temp.length())
				argQueue.push(temp);
			if (fieldLast != end)
				fieldLast++;
			it = fieldLast;
		}
	}

}
