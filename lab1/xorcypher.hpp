#ifndef XORCYPHER_HPP
#define XORCYPHER_HPP
#include <string>
#include <list>

#ifdef DEBUG
#include <iostream>
#endif

#define XORCipherKeyType std::string

class xorcypher
{
		std::string alphanum;
		std::string m_decodedMessage;
		std::string m_encodedMessage;
		XORCipherKeyType m_cipher;

		inline void checkCipherPosition(XORCipherKeyType::const_iterator& it);
		std::string getRandomString(size_t length);
	public:
		xorcypher();

		void setEncodedMessage(const std::string& sourceMessage);
		void setEncodedMessage(std::string&& sourceMessage);

		void setDecodedMessage(const std::string& sourceMessage);
		void setDecodedMessage(std::string&& sourceMessage);

		void setCipher();
		void setCipher(XORCipherKeyType&& newCipherKey);
		void setCipher(XORCipherKeyType& newCipherKey);

		std::string getDecodedMessage() const;
		std::string getEncodedMessage() const;
		XORCipherKeyType getCipher() const;

		bool encode();
		bool decode();
};

#endif // XORCYPHER_HPP
