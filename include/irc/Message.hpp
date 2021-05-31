#pragma once

#include <string> // using std::string
#include <vector> // using std::vector

#include <utils/parseField.hpp>

#include <irc/AMessage.hpp>

namespace NAMESPACE_IRC
{
	template<typename _Cmd>
	struct	Message	:	AMessage
	{
		_Cmd const*					command;
		std::vector<std::string>	arguments;

		Message();
		~Message();

		Message(_Cmd const*const commands[], size_t commandCount, std::string& buffer) throw(MessageException);
	};

	template<typename _Cmd>
	inline
	Message<_Cmd>::Message()
		: command(NULL)
	{ }

	template<typename _Cmd>
	inline
	Message<_Cmd>::~Message()
	{ }
}
