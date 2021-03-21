
# include <crypto.hpp>

# include <iostream>
# include <sstream>

static inline void
ft_uchar_cpy(unsigned char*const dest, const unsigned char*const src, size_t lenght)
throw()
{
	for (size_t i = 0 ; i < lenght ; i++)
		dest[i] = src[i];
}

/////////////////////
// Private members //
/////////////////////

inline bool
crypto::gen_hash_sha226(const std::string& msg, unsigned char* res_hash,
const std::string& __salt)
throw()
{
	SHA256_CTX	sha256_context;
	return (SHA256_Init(&sha256_context)
	&& SHA256_Update(&sha256_context, (__salt + msg).c_str(), msg.length())
	&& SHA256_Final(res_hash, &sha256_context));
}

inline const std::string
crypto::convert_to_hex(const unsigned char*const hash, size_t lenght)
throw()
{
	std::stringstream ss;

	for (size_t i = 0 ; i < lenght ; i++)
		ss << std::hex << static_cast<int>(hash[i]);
	return (std::string(ss.str()));
}

////////////////////
// PUBLIC MEMBERS //
////////////////////

crypto::crypto()
: hashed_sha256(), hexa_hash_sha256(), salt()
{ }

crypto::crypto(const std::string& __salt)
: hashed_sha256(), hexa_hash_sha256(), salt(__salt)
{ }

crypto::crypto(const crypto& other)
{ *this = other; }

crypto::~crypto()
{ }

inline crypto&
crypto::operator=(const crypto& other)
{
	if (this != &other)
	{
		ft_uchar_cpy(hashed_sha256, other.hashed_sha256, SHA256_DIGEST_LENGTH);
		hexa_hash_sha256 = other.hexa_hash_sha256;
		salt = other.salt;
	}
	return (*this);
}

inline const std::string&
crypto::get_hashed_sha256() const
throw()
{ return (hexa_hash_sha256); }

const std::string&
crypto::get_hashed_sha256(const std::string& msg)
throw(crypto_exeption)
{
	if (!gen_hash_sha226(msg, hashed_sha256, salt))
		throw crypto_exeption();
	hexa_hash_sha256 = convert_to_hex(hashed_sha256, SHA256_DIGEST_LENGTH);
	return (get_hashed_sha256());
}
