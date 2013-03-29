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
	/*
	 * XOR Functions
	 */
	QObject::connect(ui->m_XOREncodeButton, SIGNAL(clicked()), this, SLOT(XOREncode()));
	QObject::connect(ui->m_XORDecodButton, SIGNAL(clicked()), this, SLOT(XORDecode()));
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
	m_gsd.setDecodedMessage(mess.toStdWString());

	if(!m_gsd.encode()){
		QMessageBox::warning(this, "Error", "Wrong Message Data");
	} else {
		ui->m_gronsfeldEncodedMessage->setText(QString::fromWCharArray(m_gsd.getEncodedMessage().c_str()));
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
	m_gsd.setEncodedMessage(mess.toStdWString());

	if(!m_gsd.decode()){
		QMessageBox::warning(this, "Error", "Wrong Message Data");
	} else {
		ui->m_gronsfeldDecodedMessage->setText(QString::fromWCharArray(m_gsd.getDecodedMessage().c_str()));
	}
}

void MainWindow::XOREncode()
{
	QString mess = ui->m_XORDecodedMessage->toPlainText();
#ifdef DEBUG
	std::cerr << "Plain message:" << std::endl;
	std::cerr << mess.toStdString() << std::endl;
#endif
	m_xor.setDecodedMessage(mess.toStdWString());
	m_xor.setCipher();

	if(!m_xor.encode()){
		QMessageBox::warning(this, "Error", "Wrong Message Data");
	} else {
		ui->m_XOREncodedMessage->setText(QString::fromStdWString(m_xor.getEncodedMessage()));
	}
#ifdef DEBUG
//	std::cerr << "Cipher: " << std::endl;
//	std::cerr << m_xor.getCipher() << std::endl;
#endif
	ui->m_XORCipherLine->setText(QString::fromStdWString(m_xor.getCipher()));
}

void MainWindow::XORDecode()
{
	QString str = ui->m_XORCipherLine->text();

	if(!str.size()){
		QMessageBox::warning(this, "Error", "Wrong Cypher Key");
		return;
	}

	std::wstring ck = str.toStdWString();
	m_xor.setCipher(ck);

	QString mess = ui->m_XOREncodedMessage->toPlainText();
	m_xor.setEncodedMessage(mess.toStdWString());

	if(!m_xor.decode()){
		QMessageBox::warning(this, "Error", "Wrong Message Data");
	} else {
		ui->m_XORDecodedMessage->setText(QString::fromStdWString(m_xor.getDecodedMessage()));
	}
}


void MainWindow::initTabs()
{
	ui->m_gronsfeldCipherLine->setValidator(new QIntValidator(0, std::numeric_limits<int>::max(), this));

	setButtons();
}
