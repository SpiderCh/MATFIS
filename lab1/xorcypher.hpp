#ifndef XORCYPHER_HPP
#define XORCYPHER_HPP
#include <string>
#include <list>

#ifdef DEBUG
#include <iostream>
#endif

#define XORCipherKeyType std::wstring

class xorcypher
{
		std::wstring alphanum;
		std::wstring m_decodedMessage;
		std::wstring m_encodedMessage;
		XORCipherKeyType m_cipher;

		inline void checkCipherPosition(XORCipherKeyType::const_iterator& it);
		std::wstring getRandomString(size_t length);
	public:
		xorcypher();

		void setEncodedMessage(const std::wstring& sourceMessage);
		void setEncodedMessage(std::wstring&& sourceMessage);

		void setDecodedMessage(const std::wstring& sourceMessage);
		void setDecodedMessage(std::wstring&& sourceMessage);

		void setCipher();
		void setCipher(XORCipherKeyType&& newCipherKey);
		void setCipher(XORCipherKeyType& newCipherKey);

		std::wstring getDecodedMessage() const;
		std::wstring getEncodedMessage() const;
		XORCipherKeyType getCipher() const;

		bool encode();
		bool decode();
};

#endif // XORCYPHER_HPP
