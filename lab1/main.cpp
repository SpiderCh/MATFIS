#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include "rsagenerate.h"
#include "rsaencrypt.h"
#include "rsadecrypt.h"
typedef unsigned long long ull;

int main(int argc, char *argv[])
{
//	std::string mess = "hello";
//	RSAGenerate g;
//	std::pair<ull, ull> privateKey = g.getPrivateKey();
//	std::pair<ull, ull> publicKey = g.getPublicKey();

//	RSAEncrypt enc(publicKey.first, publicKey.second);
//	RSADecrypt dec(privateKey.first, privateKey.second);

//	std::list<ull> res = enc.encryptMessage(mess);
//	std::string mres = dec.decrypt(res);

//	std::cout << mres << std::endl;

//	return 0;
	QApplication a(argc, argv);
	QTextCodec* tc = QTextCodec::codecForName("utf-8");
	QTextCodec::setCodecForTr(tc);
	QTextCodec::setCodecForCStrings(tc);
	QTextCodec::setCodecForLocale(tc);
	MainWindow w;
	w.show();

	return a.exec();
}
