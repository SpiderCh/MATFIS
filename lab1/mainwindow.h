#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <limits>
#include <cmath>
#include <QImage>
#include <QStringList>

#include "gronsfeld.h"
#include "xorcypher.hpp"
#include "elgamal.hpp"
#include "rsa.h"
#include "utils.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT
		Ui::MainWindow *ui;
		void initTabs();
		void setButtons();
		QImage m_image;
		gronsfeld m_gsd;
		xorcypher m_xor;
		ElGamal m_elgamal;
		RSA m_rsa;
		QStringList m_report;
		QStringList::Iterator m_rit;
	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
		
	private slots:
		void gronsfeldEncode();
		void gronsfeldDecode();

		void XOREncode();
		void XORDecode();

		void elgamalEncode();
		void elgamalDecode();

		void RSAEncode();
		void RSADecode();

		void next();
		void prev();
};

#endif // MAINWINDOW_H
