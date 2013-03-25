#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	initTabs();
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::setButtons()
{
	/*
	 * Gronsfeld Functions
	 */
	QObject::connect(ui->m_gronsfeldEncodeButton, SIGNAL(clicked()), this, SLOT(gronsfeldEncode()));
	QObject::connect(ui->m_gronsfeldDecodButton, SIGNAL(clicked()), this, SLOT(gronsfeldDecode()));
}

void MainWindow::gronsfeldEncode()
{
	QString str = ui->m_gronsfeldCipherLine->text();

	if(!str.size()){
		QMessageBox::warning(this, "Error", "Wrong Cypher Key");
		return;
	}

	std::list<unsigned int> ck;
	char s = 0;
	for(int i = 0, size = str.size(); size > i; ++i){
		s = str[i].toAscii();
		ck.push_back(atoi(&s));
	}

	m_gsd.setCipher(ck);

	QString mess = ui->m_gronsfeldDecodedMessage->toPlainText();
	m_gsd.setDecodedMessage(mess.toStdString());

	if(!m_gsd.encode()){
		QMessageBox::warning(this, "Error", "Wrong Message Data");
	} else {
		ui->m_gronsfeldEncodedMessage->setText(m_gsd.getEncodedMessage().c_str());
	}
}

void MainWindow::gronsfeldDecode()
{
	QString str = ui->m_gronsfeldCipherLine->text();

	if(!str.size()){
		QMessageBox::warning(this, "Error", "Wrong Cypher Key");
		return;
	}

	std::list<unsigned int> ck;
	char s;
	for(size_t i = 0, size = str.size(); size > i; ++i){
		s = str[i].toAscii();
		ck.push_back(atoi(&s));
	}

	m_gsd.setCipher(ck);

	QString mess = ui->m_gronsfeldEncodedMessage->toPlainText();
	m_gsd.setEncodedMessage(mess.toStdString());

	if(!m_gsd.decode()){
		QMessageBox::warning(this, "Error", "Wrong Message Data");
	} else {
		ui->m_gronsfeldDecodedMessage->setText(m_gsd.getDecodedMessage().c_str());
	}
}


void MainWindow::initTabs()
{
	ui->m_gronsfeldCipherLine->setValidator(new QIntValidator(0, std::numeric_limits<int>::max(), this));

	setButtons();
}
