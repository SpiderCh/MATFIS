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
	return true;
}

bool gronsfeld::decode()
{
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
