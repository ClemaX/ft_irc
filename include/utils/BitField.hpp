#pragma once

template<typename Mode, typename uint_t>
struct	BitField
{
public:
	typedef uint_t	bin_t;

private:
	bin_t	modes;

public:
	BitField()
		:	modes(0)
	{ }

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
