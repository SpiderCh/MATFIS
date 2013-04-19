#include "rsadecrypt.h"

RSADecrypt::RSADecrypt(types::ull d, types::ull n):
	m_D(d),
	m_N(n)
{
}

std::string RSADecrypt::decrypt(std::list<types::ull> message)
{
	std::string result;
	for(auto it: message){
		result.push_back(math::power(it, m_D, m_N));
	}
	return result;
}
