#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <limits>
#include <cmath>

#include "gronsfeld.h"

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
	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
		
	private slots:
		void gronsfeldEncode();
		void gronsfeldDecode();
};

#endif // MAINWINDOW_H
