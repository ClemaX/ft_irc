#include <iostream>

#include <socket/ssl.hpp>

#include <utils/Logger.hpp>

namespace ssl
{
	void		init()
	{
		SSL_load_error_strings();
		OpenSSL_add_ssl_algorithms();
	}

	void		cleanup()
	{
		EVP_cleanup();
	}

	Context::Context()
		:	context(NULL)
	{ Logger::instance() << Logger::DEBUG << "Creating empty SSL context..." << std::endl; }

	Context::Context(std::string const& certPath, std::string const& keyPath)
		throw(SSLContextException)
		:	context(SSL_CTX_new(SSLv23_server_method()))
	{
		if (context == NULL)
			throw SSLContextException(errno);

		// Select elliptic curves automatically
		SSL_CTX_set_ecdh_auto(context, 1);

		Logger::instance() << Logger::DEBUG << "Creating SSL context with " << certPath << " and " << keyPath << "..." << std::endl;

		// Load SSL certificate files
		if (SSL_CTX_use_certificate_file(context, certPath.c_str(), SSL_FILETYPE_PEM) <= 0)
			throw SSLCertException(errno);
		if (SSL_CTX_use_PrivateKey_file(context, keyPath.c_str(), SSL_FILETYPE_PEM) <= 0)
			throw SSLKeyException(errno);
	}

	Context::~Context()
	{
		if (context != NULL)
		{
			Logger::instance() << Logger::DEBUG << "Destroying SSL context..." << std::endl;
			SSL_CTX_free(context);
			context = NULL;
		}
	}

	void	Context::loadCertificate(std::string const& certPath,
		std::string const& keyPath) throw(SSLContextException)
	{
		if (context == NULL)
		{
			Logger::instance() << Logger::DEBUG << "Initializing SSL context..." << std::endl;
			context = SSL_CTX_new(SSLv23_server_method());
			if (context == NULL)
				throw SSLContextException(errno);
		}

		Logger::instance() << Logger::DEBUG << "Loading SSL certificate with " << certPath << " and " << keyPath << "..." << std::endl;

		// Load SSL certificate files
		if (SSL_CTX_use_certificate_file(context, certPath.c_str(), SSL_FILETYPE_PEM) <= 0)
			throw SSLCertException(errno);
		if (SSL_CTX_use_PrivateKey_file(context, keyPath.c_str(), SSL_FILETYPE_PEM) <= 0)
			throw SSLKeyException(errno);
	}

	SSL*	Context::newConnection() const throw(SSLContextException)
		{
			if (context == NULL)
				throw SSLCertException(0);

			SSL* const	connection = SSL_new(context);

			if (connection == NULL)
				throw SSLNewException(errno);

			return connection;
		}
}
