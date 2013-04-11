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
};

#endif // MAINWINDOW_H
