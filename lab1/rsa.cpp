#include "rsa.h"

RSA::RSA():
	m_generate(),
	m_encoder(m_generate.getPublicKey().first,
			  m_generate.getPublicKey().second),
	m_decoder(m_generate.getPrivateKey().first,
			  m_generate.getPrivateKey().second)
{
}

void RSA::encode()
{
	m_encoded = m_encoder.encryptMessage(m_decoded);
}

void RSA::decode()
{
	m_decoded = m_decoder.decrypt(m_encoded);
}

void RSA::setMessage(std::string& message)
{
	m_decoded = message;
}

void RSA::setMessage(std::string&& message)
{
	m_decoded = std::move(message);
}

std::list<types::ull> RSA::getEncodedMessage()
{
	return m_encoded;
}

std::string RSA::getDecodedMessage()
{
	return m_decoded;
}

std::pair<types::ull, types::ull> RSA::getPublicKey()
{
	return m_generate.getPublicKey();
}

std::pair<types::ull, types::ull> RSA::getPrivateKey()
{
	return m_generate.getPrivateKey();
}

std::pair<types::ull, types::ull> RSA::getPQ()
{
	return m_generate.getPQ();
}
