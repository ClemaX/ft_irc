	#include <utils/itoaReply.hpp>

namespace ft
{
	std::string const&	itoaReply(unsigned int n)
	{
		static std::string	a;
		int					len;

		len = 3;

		a.resize(3);

		a[len] = '\0';

		while (len-- != 0)
		{
			a[len] = n % 10 + '0';
			n /= 10;
		}
		return a;
	}
}
