#ifndef RSAENCRYPT_H
#define RSAENCRYPT_H
#include <string>
#include <list>
#include <iostream>
#include "utils.h"

class RSAEncrypt
{
		types::ull m_E;
		types::ull m_N;

	public:

		RSAEncrypt(types::ull e,
				   types::ull n);

		std::list<types::ull> encryptMessage(std::string message);
};

#endif // RSAENCRYPT_H
