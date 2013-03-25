#ifndef XORCYPHER_HPP
#define XORCYPHER_HPP
#include <QString>
#include <string>
#include <list>

#ifdef DEBUG
#include <iostream>
#endif

#define CipherKeyType std::list<unsigned int>

class xorcypher
{
		QString alphanum;
		std::string m_decodedMessage;
		std::string m_encodedMessage;
		CipherKeyType m_cipher;
		QString m_cipherLine;

		inline void checkCipherPosition(CipherKeyType::const_iterator& it);
		QString getRandomString(size_t length);
	public:
		xorcypher();

		void setEncodedMessage(const std::string& sourceMessage);
		void setEncodedMessage(std::string&& sourceMessage);

		void setDecodedMessage(const std::string& sourceMessage);
		void setDecodedMessage(std::string&& sourceMessage);

		void setCipher();
		void setCipher(CipherKeyType&& newCipherKey);

		std::string getDecodedMessage() const;
		std::string getEncodedMessage() const;
		CipherKeyType getCipher() const;
		QString getCipherLine() const;

		bool encode();
		bool decode();
};

#endif // XORCYPHER_HPP
