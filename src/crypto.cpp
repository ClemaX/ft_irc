
# include "crypto.hpp"

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

/**
 * 	@brief Gen a new sha256 hash into @c hashed_ash256 address.
*/
inline bool
crypto::gen_hash_sha226(const std::string& msg)
throw()
{
	return (SHA256_Init(&sha256_context)
	&& SHA256_Update(&sha256_context, msg.c_str(), msg.length())
	&& SHA256_Final(hashed_sha256, &sha256_context));
}

/**
 * 	@brief Fill @c hexa_hash_sha256 using the data holded by
 * 	@c hashed_sha256 and converting it into hexadecimal format.
*/
void
crypto::convert_to_hex()
throw()
{
	std::stringstream ss;

	for (size_t i = 0 ; i < SHA256_DIGEST_LENGTH ; i++)
		ss << std::hex << static_cast<int>(hashed_sha256[i]);
	hexa_hash_sha256 = ss.str();
}

////////////////////
// PUBLIC MEMBERS //
////////////////////

crypto::crypto()
: sha256_context(), hashed_sha256(), hexa_hash_sha256()
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
		sha256_context = other.sha256_context;
		ft_uchar_cpy(hashed_sha256, other.hashed_sha256, SHA256_DIGEST_LENGTH);	
		hexa_hash_sha256 = other.hexa_hash_sha256;
	}
	return (*this);
}

inline const std::string&
crypto::get_hashed_sha256() const
throw()
{ return (hexa_hash_sha256); }

inline const std::string&
crypto::get_hashed_sha256(const std::string& msg)
throw(crypto_exeption)
{
	if (!gen_hash_sha226(msg))
		throw crypto_exeption();
	convert_to_hex();
	return (get_hashed_sha256());
}
