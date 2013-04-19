#ifndef RSAGENERATE_H
#define RSAGENERATE_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <cassert>
#include "utils.h"

class RSAGenerate
{
		types::ull m_E;
		types::ull m_D;
		types::ull m_N;
		types::ull m_P;
		types::ull m_Q;
		types::ull m_phiN;

		std::vector<types::ull> m_pn;
		std::vector<types::ull> m_ferma;

		void loadPrimeNumbers();
		void selectPQ();
		void selectE();
		void calcN();
		void calcD();
	public:
		RSAGenerate();

		std::pair<types::ull, types::ull> getPublicKey();
		std::pair<types::ull, types::ull> getPrivateKey();
		std::pair<types::ull, types::ull> getPQ();
};

#endif // RSAGENERATE_H
