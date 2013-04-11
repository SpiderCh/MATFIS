#ifndef ELGAMAL_HPP
#define ELGAMAL_HPP

#include <string>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#ifdef DEBUG
#include <iostream>
#endif

#define PType int
#define GType int

class ElGamal
{

	PType m_P;
	GType m_G;
	int m_X, m_Y;
	std::wstring m_encodedMessage;
	std::wstring m_decodedMessage;
	int powerMod(int a, int b, int n);
	int mulMod(int a, int b, int n);
public:
	ElGamal();

	void setG(GType G);
	void setP(PType P);

	void setEncodedMessage(std::wstring encodedText);
	void setDecodedMessage(std::wstring decodedText);

	std::wstring getEncodedMessage();
	std::wstring getDecodedMessage();

	bool encode();
	bool decode();
};

#endif // ELGAMAL_HPP
