#ifndef RSA_H
#define RSA_H
#include <string>
#include <list>
#include <rsagenerate.h>
#include <rsaencrypt.h>
#include <rsadecrypt.h>

class RSA
{
		RSAGenerate m_generate;
		RSAEncrypt  m_encoder;
		RSADecrypt  m_decoder;

		std::list<types::ull> m_encoded;
		std::string m_decoded;

	public:
		RSA();

		void encode();
		void decode();

		void setMessage(std::string& message);
		void setMessage(std::string&& message);

		std::list<types::ull> getEncodedMessage();
		std::string getDecodedMessage();

		std::pair<types::ull, types::ull> getPublicKey();
		std::pair<types::ull, types::ull> getPrivateKey();
		std::pair<types::ull, types::ull> getPQ();
};

#endif // RSA_H
