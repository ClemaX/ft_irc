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

	int	matchPattern(std::string const &str, std::string const &pattern)
	{
		size_t index = pattern.find('*', 0);
		if (index == std::string::npos)
			return (str.compare(pattern) != 0);

		if (str.compare(0, index, pattern, 0, index))
			return 1;

		size_t	strLength = str.length();
		size_t i = index;

		size_t	index_next = pattern.find("*", index + 1);
		if (index_next == std::string::npos)
			index_next = pattern.length();

		size_t	lengthToCheck = 0;
		if (index_next >= index + 1)
			lengthToCheck = index_next - index - 1;
		if (!lengthToCheck)
			return 0;
		if (strLength < lengthToCheck)
			lengthToCheck = strLength;

		while (i <= strLength - lengthToCheck)
		{
			if (!str.compare(i, lengthToCheck, pattern, index + 1, lengthToCheck))
			{
				if (index_next == pattern.length())
				{
					if (i + lengthToCheck == strLength)
						return 0;
					return 1;
				}
				return matchPattern(str.substr(i + lengthToCheck), pattern.substr(index_next));
			}
			i++;
		}
		return 1;
	}

}
