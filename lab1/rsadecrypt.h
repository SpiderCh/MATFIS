#ifndef RSADECRYPT_H
#define RSADECRYPT_H
#include <list>
#include <string>
#include "utils.h"

class RSADecrypt
{
		types::ull m_D;
		types::ull m_N;

	public:

		RSADecrypt(types::ull d,
				   types::ull n);

		std::string decrypt(std::list<types::ull> message);
};

#endif // RSADECRYPT_H
