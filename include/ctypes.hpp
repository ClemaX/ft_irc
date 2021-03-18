#pragma once

namespace ft
{
	inline bool	isspace(char c)
	{ return c == ' ' || (c >= '\t' && c <= '\r'); }

	inline bool	isalpha(char c)
	{ return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

	inline bool	isdigit(char c)
	{ return c >= '0' && c <= '9'; }
}
