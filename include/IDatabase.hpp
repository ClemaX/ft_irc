#pragma once

template <typename T>
class IDatabase
{
public:
	virtual ~IDatabase() { };

	virtual void	set(std::string const& key, std::string const& value) = 0;

	virtual T const&	operator[](std::string const& key) = 0;
};

