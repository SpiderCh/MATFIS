#include "gronsfeld.h"

inline void gronsfeld::checkCipherPosition(CipherKeyType::const_iterator& it)
{
	if(m_cipherKey.cend() == it){
		it = m_cipherKey.cbegin();
	}
}

void gronsfeld::performAction(const wchar_t* src, wchar_t* dst, const int direction)
{
	for(auto it = m_cipherKey.cbegin(); *src; ++it){
		checkCipherPosition(it);
		/*
		 * If we caught space key leave it untouched.
		 * In Unicode cyrillic symbols coded by 2 bytes.
		 * Skip first and encode second one. If we encode
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

void gronsfeld::setEncodedMessage(const wchar_t* message)
{
	m_encodedMessage = message;
}

void gronsfeld::setDecodedMessage(const wchar_t* message)
{
	m_decodedMessage = message;
}

void gronsfeld::setDecodedMessage(const std::wstring& sourceMessage)
{
	m_decodedMessage = sourceMessage;
#ifdef DEBUG
	std::cerr << m_decodedMessage.c_str() << std::endl;
	for(size_t i =0; i != m_decodedMessage.size(); ++i){
		std::cerr << (int)m_decodedMessage[i] << " ";
	}
	std::cerr << std::endl;
#endif
}

void gronsfeld::setDecodedMessage(std::wstring&& sourceMessage)
{
	m_decodedMessage = std::move(sourceMessage);
#ifdef DEBUG
	std::cerr << m_decodedMessage.c_str() << std::endl;
	for(size_t i =0; i != m_decodedMessage.size(); ++i){
		std::cerr << (int)m_decodedMessage[i] << " ";
	}
	std::cerr << std::endl;
#endif
}

std::wstring gronsfeld::getDecodedMessage() const
{
	return m_decodedMessage;
}

void gronsfeld::setEncodedMessage(const std::wstring& sourceMessage)
{
	m_encodedMessage = sourceMessage;
}

void gronsfeld::setEncodedMessage(std::wstring&& sourceMessage)
{
	m_encodedMessage = std::move(sourceMessage);
}

std::wstring gronsfeld::getEncodedMessage() const
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
	std::cerr << m_decodedMessage.c_str() << std::endl;
#endif

	m_encodedMessage.clear();

	if(m_decodedMessage.empty())
		return false;

	m_encodedMessage.reserve(m_decodedMessage.size() + 1);
	const wchar_t *src = m_decodedMessage.c_str(),
				  *dst = m_encodedMessage.c_str();

	performAction(src, (wchar_t*)dst, 1);
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
	std::cerr << m_encodedMessage.c_str() << std::endl;
#endif

	m_decodedMessage.clear();

	if(m_encodedMessage.empty())
		return false;

	m_decodedMessage.reserve(m_encodedMessage.size() + 1);
	const wchar_t *src = m_encodedMessage.c_str(),
			   *dst = m_decodedMessage.c_str();

	performAction(src, (wchar_t*)dst, -1);
	return true;
}
