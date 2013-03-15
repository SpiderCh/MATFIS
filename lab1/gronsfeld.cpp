#include "gronsfeld.h"

gronsfeld::gronsfeld()
{
}

void gronsfeld::setEncodedMessage(const std::string& sourceMessage)
{
	m_encodedMessage = sourceMessage;
}

void gronsfeld::setEncodedMessage(std::string&& sourceMessage)
{
	m_encodedMessage = std::move(sourceMessage);
}

void gronsfeld::setDecodedMessage(const std::string& sourceMessage)
{
	m_decodedMessage = sourceMessage;
}

void gronsfeld::setDecodedMessage(std::string&& sourceMessage)
{
	m_decodedMessage = std::move(sourceMessage);
}

std::string gronsfeld::getDecodedMessage() const
{
	return m_decodedMessage;
}

std::string gronsfeld::getEncodedMessage() const
{
	return m_encodedMessage;
}

CipherType gronsfeld::getCipher() const
{
	return m_cipher;
}

bool gronsfeld::encode()
{
	m_encodedMessage.clear();

	if(m_decodedMessage.empty())
		return false;

	const size_t size = m_decodedMessage.size();
	const size_t cipherSize = m_cipher.size();

	const char* symbol = m_decodedMessage.c_str();

	for(size_t index = 0, cipherIndex = 0; size != index; ++symbol, ++index, ++cipherIndex){
		if(cipherSize == cipherIndex){
			cipherIndex = 0;
		}
		/*
		 * In Unicode cyrillic symbols coded by 2 bytes.
		 * Skip firt and encode second one. If we encode
		 * first byte we get garbage in string
		 */
		if(*symbol < 0){
			m_encodedMessage.push_back(*symbol);
		}
		m_encodedMessage.push_back(*symbol + m_cipher[cipherIndex]);
	}
	return true;
}

bool gronsfeld::decode()
{
	m_decodedMessage.clear();

	if(m_encodedMessage.empty())
		return false;

	const size_t size = m_encodedMessage.size();
	const size_t cipherSize = m_cipher.size();

	const char* symbol = m_encodedMessage.c_str();

	for(size_t index = 0, cipherIndex = 0; size != index; ++symbol, ++index, ++cipherIndex){
		if(cipherSize == cipherIndex){
			cipherIndex = 0;
		}
		/*
		 * In Unicode cyrillic symbols coded by 2 bytes.
		 * Skip firt and encode second one. If we encode
		 * first byte we get garbage in string
		 */
		if(*symbol < 0){
			m_decodedMessage.push_back(*symbol);
		}
		m_decodedMessage.push_back(*symbol - m_cipher[cipherIndex]);
	}
	return true;
}

void  gronsfeld::setCipher(const CipherType& newCipher)
{
	m_cipher = newCipher;
}

void gronsfeld::setCipher(CipherType&& newCipher)
{
	m_cipher = std::move(newCipher);
}
