#include "xorcypher.hpp"

inline void xorcypher::checkCipherPosition(XORCipherKeyType::const_iterator& it)
{
	if(m_cipher.cend() == it){
		it = m_cipher.cbegin();
	}
}

std::string xorcypher::getRandomString(size_t length)
{
	std::string output;
#ifdef DEBUG
	std::cerr << "Length of message:" << std::endl;
	std::cerr << length << std::endl;
#endif
	for (size_t i = 0; i < length; ++i) {
		output += alphanum[rand() % (alphanum.size() - 1)];
	}
#ifdef DEBUG
	std::cerr << "Generated string for cipher:" << std::endl;
	std::cerr << output << std::endl;
#endif
	return output;
}

xorcypher::xorcypher()
{
	alphanum =
			"0123456789"
			"!@#$%^&*"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
}


void xorcypher::setEncodedMessage(const std::string& sourceMessage)
{
	m_encodedMessage = sourceMessage;
}

void xorcypher::setEncodedMessage(std::string&& sourceMessage)
{
	m_encodedMessage = std::move(sourceMessage);
}

void xorcypher::setDecodedMessage(const std::string& sourceMessage)
{
	m_decodedMessage = sourceMessage;
}

void xorcypher::setDecodedMessage(std::string&& sourceMessage)
{
	m_decodedMessage = std::move(sourceMessage);
}

std::string xorcypher::getDecodedMessage() const
{
	return m_decodedMessage;
}

std::string xorcypher::getEncodedMessage() const
{
	return m_encodedMessage;
}

XORCipherKeyType xorcypher::getCipher() const
{
	return m_cipher;
}

bool xorcypher::encode()
{
#ifdef DEBUG
	std::cerr << "Key:" << std::endl;
	XORCipherKeyType::const_iterator it = m_cipher.cbegin();
	const XORCipherKeyType::const_iterator end = m_cipher.cend();
	for(; it != end; ++it){
		std::cerr << *it << " ";
	}
	std::cerr << std::endl;

	std::cerr << "Message:" << std::endl;
	std::cerr << m_decodedMessage << std::endl;
#endif
	m_encodedMessage.clear();

	if(m_decodedMessage.empty())
		return false;
	const char* symbol = m_decodedMessage.c_str();

	for(XORCipherKeyType::const_iterator it = m_cipher.cbegin(); *symbol; ++it){
		checkCipherPosition(it);
		/*
		 * In Unicode cyrillic symbols coded by 2 bytes.
		 * Skip first and encode second one. If we encode
		 * first byte we get garbage in string
		 */
		if(*symbol < 0){
			m_encodedMessage.push_back(*symbol++);
		}
		m_encodedMessage.push_back(*symbol++ ^ *it);
	}
	return true;
}

bool xorcypher::decode()
{
	m_decodedMessage.clear();

	if(m_encodedMessage.empty())
		return false;

	const char* symbol = m_encodedMessage.c_str();

	for(XORCipherKeyType::const_iterator it = m_cipher.cbegin(); *symbol; ++it){
		checkCipherPosition(it);
		/*
		 * In Unicode cyrillic symbols coded by 2 bytes.
		 * Skip firt and encode second one. If we encode
		 * first byte we get garbage in string
		 */
		if(*symbol < 0){
			m_decodedMessage.push_back(*symbol++);
		}
		m_decodedMessage.push_back(*symbol++ ^ *it);
	}
	return true;
}

void  xorcypher::setCipher()
{
	m_cipher.clear();
#ifdef DEBUG
	std::cerr << "Length of plain text:" << std::endl;
	std::cerr << m_decodedMessage.length() << std::endl;
#endif
	m_cipher = getRandomString(m_decodedMessage.length());
}

void xorcypher::setCipher(XORCipherKeyType&& newCipherKey)
{
	m_cipher.clear();
	m_cipher = std::move(newCipherKey);
}

void xorcypher::setCipher(XORCipherKeyType& newCipherKey)
{
	m_cipher.clear();
	m_cipher = newCipherKey;
}
