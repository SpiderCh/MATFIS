#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <limits>
#include <cmath>

#include "gronsfeld.h"
#include "xorcypher.hpp"

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
	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
		
	private slots:
		void gronsfeldEncode();
		void gronsfeldDecode();

		void XOREncode();
		void XORDecode();
};

#endif // MAINWINDOW_H
