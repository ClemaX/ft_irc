#pragma once

#include <iostream>
#include <fstream>

#include <string>
#include <map>

#include <IDatabase.hpp>

#define DB_ENDL '\n'
#define DB_PADDING ' '

class FileDatabase	:	public IDatabase<std::string>
{
private:
	std::fstream	file;

	unsigned		keyLength;
	unsigned		valueLength;

	std::map<std::string, std::string>	data;

	char*	keyBuffer;
	char*	valueBuffer;

	bool	seekToKey(std::string const& key)
	{
		std::streampos	readPos = 0;

		while (file.peek() != std::string::traits_type::eof())
		{
			file.get(keyBuffer, keyLength + 1, DB_PADDING);

			if (keyBuffer == key)
			{
				file.seekg(0);
				file.seekp(readPos);
				return true;
			}

			readPos += keyLength;
			file.seekg(readPos);
			file.get(valueBuffer, valueLength + 1, DB_PADDING);
			readPos += valueLength + sizeof(DB_ENDL);
			file.seekg(readPos);
		}
		file.seekg(0);
		file.seekp(readPos);
		return false;
	}

	// TODO: Use seekToKey
	bool	seekToValue(std::string const& key)
	{
		std::streampos	readPos = 0;

		while (file.peek() != std::string::traits_type::eof())
		{
			file.get(keyBuffer, keyLength + 1, DB_PADDING);
			readPos += keyLength;

			if (keyBuffer == key)
			{
				file.seekg(0);
				file.seekp(readPos);
				return true;
			}

			file.seekg(readPos);
			file.get(valueBuffer, valueLength + 1, DB_PADDING);
			readPos += valueLength + sizeof(DB_ENDL);
			file.seekg(readPos);
		}
		file.seekg(0);
		file.seekp(readPos);
		return false;
	}

public:
	class	Exception			:	public std::exception { };

	class	OverflowException	:	public Exception
	{
	public:
		char const*	what() const throw() { return "Data overflows line size"; }
	};

	FileDatabase(std::string const& filepath, unsigned keyLength,
		unsigned valueLength)
		:	file(filepath.c_str()),
			keyLength(keyLength),
			valueLength(valueLength)
	{
		keyBuffer = new char [keyLength];
		valueBuffer = new char [valueLength];

		std::streampos	readPos = 0;

		while (file.peek() != std::string::traits_type::eof())
		{
			file.get(keyBuffer, keyLength + 1, DB_PADDING);
			readPos += keyLength;
			file.seekg(readPos);

			file.get(valueBuffer, valueLength + 1, DB_PADDING);
			readPos += valueLength + sizeof(DB_ENDL);
			file.seekg(readPos);

			data[keyBuffer] = valueBuffer;
		}
		file.seekg(0);
		file.clear();
	}

	~FileDatabase()
	{
		delete[] keyBuffer;
		delete[] valueBuffer;
	}

	virtual void	set(std::string const& key, std::string const& value)
		throw (OverflowException)
	{
		std::cout << "valueLength: " << value.length() << std::endl;
		if (key.length() > keyLength || value.length() > valueLength)
			throw OverflowException();

		const unsigned	keyPadding = keyLength - key.length();
		const unsigned	valuePadding = valueLength - value.length();
		const bool		newline = !seekToValue(key);

		if (newline)
		{
			file << key;
			if (keyPadding)
				file << std::string(keyPadding, DB_PADDING);
		}

		file << value;
		if (valuePadding)
			file << std::string(valuePadding, DB_PADDING);

		if (newline)
			file << DB_ENDL;

		file.flush();

		data[key] = value;
	}

	virtual std::string const&	operator[](std::string const& key)
	{ return data[key]; }
};
