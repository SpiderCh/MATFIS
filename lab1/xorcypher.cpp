#include "xorcypher.hpp"

inline void xorcypher::checkCipherPosition(CipherKeyType::const_iterator& it)
{
	if(m_cipher.cend() == it){
		it = m_cipher.cbegin();
	}
}

QString xorcypher::getRandomString(size_t length)
{
	QString output;
#ifdef DEBUG
	std::cerr << length << std::endl;
#endif
	for (size_t i = 0; i < length; ++i) {
		output += alphanum[rand() % (sizeof(alphanum) - 1)];
	}
	output += '\0';
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

CipherKeyType xorcypher::getCipher() const
{
	return m_cipher;
}

QString xorcypher::getCipherLine() const
{
	return m_cipherLine;
}

bool xorcypher::encode()
{
#ifdef DEBUG
	std::cerr << "Key:" << std::endl;
	CipherType::const_iterator it = m_cipher.cbegin();
	const CipherType::const_iterator end = m_cipher.cend();
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

	for(CipherKeyType::const_iterator it = m_cipher.cbegin(); *symbol; ++it){
		checkCipherPosition(it);
		/*
		 * In Unicode cyrillic symbols coded by 2 bytes.
		 * Skip firt and encode second one. If we encode
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

	for(CipherKeyType::const_iterator it = m_cipher.cbegin(); *symbol; ++it){
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
	m_cipherLine = getRandomString(m_decodedMessage.length());
	char s = 0;
	for(size_t i = 0, size = m_cipherLine.size(); i < size; i++){
		s = m_cipherLine[i].toAscii();
		m_cipher.push_back(atoi(&s));
	}
}

void xorcypher::setCipher(CipherKeyType&& newCipherKey)
{
	m_cipher.clear();
	m_cipher = std::move(newCipherKey);
}
