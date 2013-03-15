#ifndef GRONSFELD_H
#define GRONSFELD_H
#include <string>
#include <vector>

#define CipherType std::vector<unsigned int>

class gronsfeld
{
		std::string m_decodedMessage;
		std::string m_encodedMessage;
		CipherType m_cipher;
	public:
		gronsfeld();

		void setEncodedMessage(const std::string& sourceMessage);
		void setEncodedMessage(std::string&& sourceMessage);

		void setDecodedMessage(const std::string& sourceMessage);
		void setDecodedMessage(std::string&& sourceMessage);

		void setCipher(const CipherType& newCipher);
		void setCipher(CipherType&& newCipher);

		std::string getDecodedMessage() const;
		std::string getEncodedMessage() const;
		CipherType getCipher() const;

		bool encode();
		bool decode();
};

#endif // GRONSFELD_H
