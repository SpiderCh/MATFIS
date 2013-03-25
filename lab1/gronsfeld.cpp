#include "gronsfeld.h"

inline void gronsfeld::checkCipherPosition(CipherKeyType::const_iterator& it)
{
	if(m_cipherKey.cend() == it){
		it = m_cipherKey.cbegin();
	}
}

void gronsfeld::performAction(const char* src, char* dst, const int direction)
{
	for(auto it = m_cipherKey.cbegin(); *src; ++it){
		checkCipherPosition(it);
		/*
		 * If we caught space key leave it untouched.
		 * In Unicode cyrillic symbols coded by 2 bytes.
		 * Skip firt and encode second one. If we encode
		 * first byte we get garbage in string
		 */
		if(*src == ' '){
			*dst++ = *src++;
			continue;
		} else if(*src < 0){
			*dst++ = *src++;
		}
		*dst++ = *src++ + direction * *it;
	}
	*dst = *src;
}

gronsfeld::gronsfeld()
{
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

void gronsfeld::setEncodedMessage(const std::string& sourceMessage)
{
	m_encodedMessage = sourceMessage;
}

void gronsfeld::setEncodedMessage(std::string&& sourceMessage)
{
	m_encodedMessage = std::move(sourceMessage);
}

std::string gronsfeld::getEncodedMessage() const
{
	return m_encodedMessage;
}

void  gronsfeld::setCipher(const CipherKeyType& newCipherKey)
{
	m_cipherKey.clear();
	m_cipherKey = newCipherKey;
}

void gronsfeld::setCipher(CipherKeyType&& newCipherKey)
{
	m_cipherKey.clear();
	m_cipherKey = std::move(newCipherKey);
}

CipherKeyType gronsfeld::getCipher() const
{
	return m_cipherKey;
}

bool gronsfeld::encode()
{
#ifdef DEBUG
	std::cerr << "Key:" << std::endl;
	CipherKeyType::const_iterator it = m_cipherKey.cbegin();
	const CipherKeyType::const_iterator end = m_cipherKey.cend();
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

	m_encodedMessage.reserve(m_decodedMessage.size() + 1);
	const char *src = m_decodedMessage.c_str(),
			   *dst = m_encodedMessage.c_str();

	performAction(src, (char*)dst, 1);
	return true;
}

bool gronsfeld::decode()
{
#ifdef DEBUG
	std::cerr << "Key:" << std::endl;
	CipherKeyType::const_iterator it = m_cipherKey.cbegin();
	const CipherKeyType::const_iterator end = m_cipherKey.cend();
	for(; it != end; ++it){
		std::cerr << *it << " ";
	}
	std::cerr << std::endl;

	std::cerr << "Message:" << std::endl;
	std::cerr << m_encodedMessage << std::endl;
#endif

	m_decodedMessage.clear();

	if(m_encodedMessage.empty())
		return false;

	m_decodedMessage.reserve(m_encodedMessage.size() + 1);
	const char *src = m_encodedMessage.c_str(),
			   *dst = m_decodedMessage.c_str();

	performAction(src, (char*)dst, -1);
	return true;
}
