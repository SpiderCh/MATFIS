#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <limits>
#include <cmath>

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

		gronsfeld m_gsd;
		xorcypher m_xor;
		ElGamal m_elgamal;
		RSA m_rsa;
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
};

#endif // MAINWINDOW_H
