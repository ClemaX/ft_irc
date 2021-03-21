#pragma once

template <typename T>
class IDatabase
{
private:

public:
	IDatabase() { };
	virtual ~IDatabase() { };

	virtual void	set(std::string const& key, std::string const& value) = 0;

	virtual T const&	operator[](std::string const& key) = 0;
};

