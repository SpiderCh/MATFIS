#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec* tc = QTextCodec::codecForName("utf-8");
	QTextCodec::setCodecForTr(tc);
	QTextCodec::setCodecForCStrings(tc);
	QTextCodec::setCodecForLocale(tc);
	MainWindow w;
	w.show();

	return a.exec();
}
