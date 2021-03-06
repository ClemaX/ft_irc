#pragma once

template<typename Mode, typename uint_t, uint_t modeMax>
struct	BitField
{
public:
	typedef uint_t	bin_t;

private:
	bin_t	modes;

public:
	BitField(): modes(0) {}

	BitField(bin_t initialModes)
		: modes(initialModes)
	{}

	std::string
	toString(const char* const symbols[]) const
	{
		std::string res = "+";

		for (size_t i = 1 ; i <= modeMax ; i <<= 1)
			if (modes & i)
				res += symbols[i];
		return (res);
	}

	bool	operator[](Mode mode) const
	{ return modes & mode; }

	bin_t	operator|(bin_t modeMask) const
	{ return modes | modeMask; }

	bin_t	operator&(bin_t modeMask) const
	{ return modes & modeMask; }

	bin_t	operator^(bin_t modeMask) const
	{ return modes ^ modeMask; }

	BitField&	operator=(bin_t newModes)
	{ modes = newModes; return *this; }

	BitField&	operator|=(bin_t modeMask)
	{ modes |= modeMask; return *this; }

	BitField&	operator&=(bin_t modeMask)
	{ modes &= modeMask; return *this; }

	void	set(bin_t modeMask)
	{ modes |= modeMask; }

	void	set(Mode mode)
	{ modes |= mode; };

	void	unset(Mode mode)
	{ modes &= ~mode; }

	void	unset(bin_t modeMask)
	{ modes &= ~modeMask; }

	void	toggle(bin_t modeMask)
	{ modes ^= modeMask; }

	void	toggle(Mode mode)
	{ modes ^= mode; }

	bool	operator==(bin_t rhs) const
	{ return modes == rhs; }
};
