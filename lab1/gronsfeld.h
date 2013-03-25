#ifndef GRONSFELD_H
#define GRONSFELD_H
#include <string>
#include <list>

#ifdef DEBUG
#include <iostream>
#endif

#define CipherKeyType std::list<unsigned int>

class gronsfeld
{
		std::string m_decodedMessage;
		std::string m_encodedMessage;
		CipherKeyType m_cipherKey;

		inline void checkCipherPosition(CipherKeyType::const_iterator& it);

		void performAction(const char *src, char* dst, const int direction);
	public:
		gronsfeld();

		void setEncodedMessage(const std::string& sourceMessage);
		void setEncodedMessage(std::string&& sourceMessage);

		void setDecodedMessage(const std::string& sourceMessage);
		void setDecodedMessage(std::string&& sourceMessage);

		void setCipher(const CipherKeyType& newCipherKey);
		void setCipher(CipherKeyType&& newCipherKey);

		std::string getDecodedMessage() const;
		std::string getEncodedMessage() const;
		CipherKeyType getCipher() const;

		bool encode();
		bool decode();
};

#endif // GRONSFELD_H
