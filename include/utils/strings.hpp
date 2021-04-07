#pragma once

#include <cstddef>

namespace ft
{
	inline void    bzero(void *s, size_t n)
	{
		char *temp = static_cast<char*>(s);

		while (n--)
			*temp++ = 0;
	}
}
