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
		std::wstring m_decodedMessage;
		std::wstring m_encodedMessage;
		CipherKeyType m_cipherKey;

		inline void checkCipherPosition(CipherKeyType::const_iterator& it);

		void performAction(const wchar_t *src, wchar_t* dst, const int direction);
	public:
		gronsfeld();

		void setEncodedMessage(const wchar_t* message);
		void setEncodedMessage(const std::wstring& sourceMessage);
		void setEncodedMessage(std::wstring&& sourceMessage);

		void setDecodedMessage(const wchar_t* message);
		void setDecodedMessage(const std::wstring& sourceMessage);
		void setDecodedMessage(std::wstring&& sourceMessage);

		void setCipher(const CipherKeyType& newCipherKey);
		void setCipher(CipherKeyType&& newCipherKey);

		std::wstring getDecodedMessage() const;
		std::wstring getEncodedMessage() const;
		CipherKeyType getCipher() const;

		bool encode();
		bool decode();
};

#endif // GRONSFELD_H
