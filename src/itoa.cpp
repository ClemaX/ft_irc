#include <itoa.hpp>

namespace ft
{
	static int      uintlen(unsigned int n)
	{
			int len;

			len = 1;
			while (n /= 10)
					len++;
			return len;
	}

	std::string const&	itoa(int n)
	{
		static std::string	a;
		unsigned int		u_n;
		int					len;
		char				sign;

		sign = (n < 0);
		u_n = (sign) ? -n : n;
		len = uintlen(u_n) + sign;

		a.resize(len);

		if (sign)
				a[0] = '-';

		a[len] = '\0';

		while (len-- != sign)
		{
			a[len] = u_n % 10 + '0';
			u_n /= 10;
		}
		return a;
	}
}
