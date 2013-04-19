#include "rsaencrypt.h"

RSAEncrypt::RSAEncrypt(types::ull e, types::ull n):
	m_E(e),
	m_N(n)
{
#ifdef DEBUG
	std::cerr << "e:\t" << e << std::endl;
	std::cerr << "n:\t" << n << std::endl;
#endif
}

std::list<types::ull> RSAEncrypt::encryptMessage(std::string message)
{
	size_t size = message.size();
	std::list<types::ull> result;
	types::ull sym;
	for(unsigned i = 0; i != size; ++i){
		sym = static_cast<int>(message.c_str()[i]);
		result.push_back(math::power(sym, m_E, m_N));
	}

	return result;
}
