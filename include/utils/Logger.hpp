#pragma once

#include <string>

#include <fstream>

class	Singleton
{
public:
	Singleton()
	{ }

	static Singleton&	instance()
	{
		static Singleton	singletonInstance;

		return singletonInstance;
	}
};

class	ILogger	:	public Singleton
{
public:
	enum	Level
	{
		DEBUG = 0,
		INFO,
		WARNING,
		ERROR,
		_LAST // Only used to get the max level, should always be last
	};

	virtual void	log(std::string const& message, Level level = INFO) = 0;

	virtual std::ostream& operator<<(Level level) = 0;
};

class	Logger	:	public ILogger
{
protected:
	std::ofstream	destination;
	std::ofstream	nullStream;

	Level			minLevel;

public:
	static char const*const	levelNames[_LAST];
	static char const		levelFieldWidth;

	~Logger();

	static Logger&	instance(std::string const& filepath = "/dev/stderr",
		Level minLevel = INFO);

	virtual void	log(std::string const& message, Level level = INFO);

	virtual std::ostream& operator<<(Level level);

	// TODO: Add throw specification for file open
	void			setFile(std::string const& filepath);
	void			setLevel(Level level) throw();
	void			setLevel(std::string const& levelName) throw(std::domain_error);

private:
	Logger(std::string const& filepath = "/dev/stderr", Level minLevel = INFO);

	Logger&	operator=(Logger const&)
	{ return *this; };
};
