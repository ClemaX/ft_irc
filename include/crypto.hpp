
# pragma once

# include <openssl/sha.h>
# include <string>

class crypto_exeption
: public std::exception
{
	const char* what() const throw()
	{ return ("crypto exeption"); }
};

class crypto
{
    SHA256_CTX			sha256_context;
    unsigned char		hashed_sha256[SHA256_DIGEST_LENGTH];
	std::string			hexa_hash_sha256;

	bool				gen_hash_sha226(const std::string& msg) throw();
	void				convert_to_hex() throw();

	public:

	crypto();
	crypto(const crypto& other);
	~crypto();

	crypto& operator=(const crypto& other);

	const std::string&	get_hashed_sha256() const throw();
	const std::string&	get_hashed_sha256(const std::string& msg) throw(crypto_exeption);
};
