#pragma once

#include <FileDatabase.hpp>

#include <utils/crypto.hpp>

class HashedFileDatabase	:	public FileDatabase
{
private:
	crypto	hasher;

public:
	HashedFileDatabase(std::string const& filepath, unsigned keyLength,
		unsigned valueLength) : FileDatabase(filepath, keyLength, valueLength)
	{ }

	virtual void	set(std::string const& key, std::string const& value)
		throw(OverflowException)
	{ FileDatabase::set(key, hasher.get_hashed_sha256(value)); }
};
