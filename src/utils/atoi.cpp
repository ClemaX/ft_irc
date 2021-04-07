#include <utils/atoi.hpp>

namespace ft
{
	int	atoi(std::string const& str)
	{
		char						factor;
		unsigned long				max;
		unsigned long				i;
		std::string::const_iterator	it = str.begin();

		while (ft::isspace(*it))
			it++;
		factor = (*it == '-') ? -1 : 1;
		it += (*it == '-' || *it == '+');
		max = (factor < 0) ? LONG_MIN : LONG_MAX;
		i = 0;
		while (ft::isdigit(*it) && i < max)
			i = i * 10 + (*it++ - '0');
		if (i >= max)
			return ((factor < 0) ? 0 : -1);
		return (i * factor);
	}
}
