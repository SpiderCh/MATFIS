#include "rsagenerate.h"

RSAGenerate::RSAGenerate():
	m_E(0),
	m_D(0),
	m_N(0),
	m_P(0),
	m_Q(0),
	m_phiN(0)
{
	m_ferma.push_back(5);
	m_ferma.push_back(17);
	m_ferma.push_back(257);
	m_ferma.push_back(65537);

	loadPrimeNumbers();
	selectPQ();
	calcN();
	selectE();
	calcD();

#ifdef DEBUG
	std::cerr << "p:\t" << m_P << std::endl;
	std::cerr << "q:\t" << m_Q << std::endl;
	std::cerr << "e:\t" << m_E << std::endl;
	std::cerr << "d:\t" << m_D << std::endl;
	std::cerr << "n:\t" << m_N << std::endl;
	std::cerr << "phiN:\t" << m_phiN << std::endl;
#endif
}

std::pair<types::ull, types::ull> RSAGenerate::getPublicKey()
{
	return std::make_pair(m_E, m_N);
}

std::pair<types::ull, types::ull> RSAGenerate::getPrivateKey()
{
	return std::make_pair(m_D, m_N);
}

std::pair<types::ull, types::ull> RSAGenerate::getPQ()
{
	return std::make_pair(m_P, m_Q);
}


void RSAGenerate::loadPrimeNumbers()
{
#ifdef DEBUG
	std::cerr << "Reading PN" << std::endl;
#endif
	types::ull val = 0;
	std::string file = "../prime-2032.txt";
	std::fstream in;
	in.open(file, std::ios::in);
	m_pn.reserve(1065);
	while(in.good()){
		in >> val;
		m_pn.push_back(val);
	}
#ifdef DEBUG
	std::cerr << "Reading PN Finished" << std::endl;
	std::cerr << "Readed: " << m_pn.size() << std::endl;
#endif
}

void RSAGenerate::selectPQ()
{
	unsigned long pPos = Random::generate(m_pn.size());
	unsigned long qPos = Random::generate(m_pn.size());
	while(pPos == qPos){
		qPos = Random::generate(m_pn.size());
	}

	m_P = m_pn[pPos];
	m_Q = m_pn[qPos];
}

void RSAGenerate::selectE()
{
	do {
		unsigned ePos = Random::generate(m_ferma.size());
		m_E = m_ferma[ePos];
	} while((m_E < 1) && (m_E > m_phiN));

	assert(m_E != 0);
	assert(m_E < 65537);
}

void RSAGenerate::calcN()
{
	m_N = m_P * m_Q;
	m_phiN = (m_P - 1) * (m_Q - 1);
}

void RSAGenerate::calcD()
{
	m_D = 0;
	while ((m_D * m_E) % m_phiN != 1) {
		++m_D;
	}
}
