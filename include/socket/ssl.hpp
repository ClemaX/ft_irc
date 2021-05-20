#pragma once
#include <openssl/ssl.h>
#include <openssl/err.h>

#include <socket/SocketExceptions.hpp>

#include <string>

namespace ssl
{
	void		init();
	void		cleanup();

	class Context
	{
	private:
		SSL_CTX*	context;

		Context& operator=(Context const&)
		{ return *this; }

		Context(Context const&)
		{ }

	public:
		Context();
		~Context();

		Context(std::string const& certPath, std::string const& keyPath)
			throw(SSLContextException);

		void	loadCertificate(std::string const& certPath,
			std::string const& keyPath)
			throw(SSLContextException);

		SSL*	newConnection() const throw(SSLContextException);
	};
}
