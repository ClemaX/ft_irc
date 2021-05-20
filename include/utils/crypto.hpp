#pragma once

#include <openssl/sha.h>
#include <string>

struct crypto_exeption
: public std::exception
{
	const char* what() const throw()
	{ return ("crypto exeption"); }
};

class crypto
{
    unsigned char		hashed_sha256[SHA256_DIGEST_LENGTH];
	std::string			hexa_hash_sha256;
	std::string			salt;

	static bool					gen_hash_sha226(const std::string& msg, unsigned char* res_hash,
								const std::string& salt) throw();
	static const std::string	convert_to_hex(const unsigned char*const hash, size_t lenght) throw();

	public:

	crypto();
	crypto(const std::string& salt);
	crypto(const crypto& other);
	~crypto();

	crypto&	operator=(const crypto& other);

	const std::string&	get_hashed_sha256() const throw();
	const std::string&	get_hashed_sha256(const std::string& msg) throw(crypto_exeption);
};
