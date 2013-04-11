#include "elgamal.hpp"

ElGamal::ElGamal()
{
}

void ElGamal::setG(int G)
{
	m_G = G;
}

void ElGamal::setP(int P)
{
	m_P = P;
}

void ElGamal::setEncodedMessage(std::wstring encodedText)
{
	m_encodedMessage = encodedText;
}

void ElGamal::setDecodedMessage(std::wstring decodedText)
{
	m_decodedMessage = decodedText;
}

std::wstring ElGamal::getEncodedMessage()
{
	return m_encodedMessage;
}

std::wstring ElGamal::getDecodedMessage()
{
	return m_decodedMessage;
}

bool ElGamal::encode()
{
	m_encodedMessage.clear();
	if(m_decodedMessage.empty())
		return false;
#ifdef DEBUG
	for(int i = 0; i < m_decodedMessage.length(); i++){
	std::wcerr << "Decoded[" << i << "]: " << m_decodedMessage[i] << std::endl;
	}
#endif
	srand(time(NULL));
	m_X = rand() % (m_P - 2) + 1;
	m_Y = powerMod(m_G, m_X, m_P);
	for (int i = 0; i < m_decodedMessage.length(); i++){
			int K = rand() % (m_P - 2) + 1;
			int a = powerMod(m_G, K, m_P);
			int b = mulMod(powerMod(m_Y, K, m_P), m_decodedMessage[i], m_P);
#ifdef DEBUG
			std::cerr << "K: " << K << std::endl;
			std::wcerr << "a: " << (wchar_t)a << std::endl;
			std::wcerr << "b: " << (wchar_t)b << std::endl;
#endif
			m_encodedMessage += (wchar_t) a;
			m_encodedMessage += (wchar_t) b;
		}
	return true;
}

bool ElGamal::decode()
{
	m_decodedMessage.clear();
	if(m_encodedMessage.empty())
		return false;

	for (int i = 0; i < m_encodedMessage.length() - 1; i+= 2){
		int a = (int)m_encodedMessage[i];
		int b = (int)m_encodedMessage[i+1];
		int msg = mulMod(b, powerMod(a, m_P - 1 - m_X, m_P), m_P);

		wchar_t sym = static_cast<wchar_t> (msg);
#ifdef DEBUG
		std::wcerr << "Sym: " << sym << std::endl;
#endif
		m_decodedMessage += sym;
	}
	return true;
}


int ElGamal::powerMod(int a, int b, int n)
{
	int tmp = a;
	int sum = tmp;
	for(int i = 1; i < b; i++){
		for(int j = 1; j < a; j++){
			sum += tmp;
			if(sum >= n) sum -= n;
		}
		tmp = sum;
	}
	return tmp;
}

int ElGamal::mulMod(int a, int b, int n)
{
	int sum = 0;
	for(int i = 0; i < b; i++){
		sum += a;
		if(sum >= n) sum -= n;
	}
	return sum;
}
