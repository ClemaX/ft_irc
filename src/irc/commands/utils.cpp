#include <irc/Server.hpp>


namespace NAMESPACE_IRC
{
	// SocketConnection const&	operator<<(SocketConnection const& client, IReply const& message)
	// {
	// 	client << message.serialize();

	// 	return client;
	// }


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

	bool	matchPattern_multiple(std::string const &str, std::string const &pattern)
	{
		size_t index = pattern.find('*', 0);
		if (index == std::string::npos)
			return !str.compare(pattern);

		if (str.compare(0, index, pattern, 0, index))
			return false;

		if (!str.length())
			return matchPattern_global(str, pattern.substr(index + 1));

		size_t	strLength = str.length();
		size_t i = index;

		size_t	index_next = pattern.find('*', index + 1);
		size_t	index_next_unique = pattern.find('?', index + 1);
		if (index_next > index_next_unique)
			index_next = index_next_unique;
		if (index_next == std::string::npos)
			index_next = pattern.length();

		size_t	lengthToCheck = 0;
		if (index_next > index)
			lengthToCheck = index_next - index - 1;
		if (!lengthToCheck)
			return true;
		if (strLength < lengthToCheck)
			lengthToCheck = strLength;

		while (i <= strLength - lengthToCheck)
		{
			if (!str.compare(i, lengthToCheck, pattern, index + 1, lengthToCheck))
			{
				if (index_next == pattern.length())
				{
					if (i + lengthToCheck == strLength)
						return true;
					return false;
				}
				return matchPattern_global(str.substr(i + lengthToCheck), pattern.substr(index_next));
			}
			i++;
		}
		return false;
	}

	bool	matchPattern_unique(std::string const &str, std::string const &pattern)
	{

		size_t index = pattern.find('?', 0);
		if (index == std::string::npos)
			return !str.compare(pattern);

		if (str.length() <= index)
			return false;

		if (str.compare(0, index, pattern, 0, index))
			return false;

		return matchPattern_global(str.substr(index + 1), pattern.substr(index + 1));
	}

	bool	matchPattern_global(std::string const &str, std::string const &pattern)	// one case not managed : when ? is right after *
	{
		size_t index_unique = pattern.find('?', 0);
		size_t index_multiple = pattern.find('*', 0);

		if (index_unique >= index_multiple)
			return matchPattern_multiple(str, pattern);
		return matchPattern_unique(str, pattern);
	}

}
