#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	m_rsa()
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
	/*
	 * ElGamal Functions
	 */
	QObject::connect(ui->m_elGamalEncodeButton, SIGNAL(clicked()), this, SLOT(elgamalEncode()));
	QObject::connect(ui->m_elGamalDecodButton, SIGNAL(clicked()), this, SLOT(elgamalDecode()));
	/*
	 * RSA Functions
	 */
	QObject::connect(ui->m_RSAEncode, SIGNAL(clicked()), this, SLOT(RSAEncode()));
	QObject::connect(ui->m_RSADecode, SIGNAL(clicked()), this, SLOT(RSADecode()));
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
		ui->m_XORDecodedMessage->append(QString::fromStdWString(m_xor.getDecodedMessage()));
	}
}

void MainWindow::elgamalEncode()
{
	QString str = ui->m_elGamalPLine->text();
	if(!str.size()){
		QMessageBox::warning(this, "Error", "Wrong P");
		return;
	}
	m_elgamal.setP(str.toInt());
	str = ui->m_elGamalGLine->text();
	if(!str.size()){
		QMessageBox::warning(this, "Error", "Wrong G");
		return;
	}
	m_elgamal.setG(str.toInt());
	str = ui->m_elGamalDecodedMessage->toPlainText();
	m_elgamal.setDecodedMessage(str.toStdWString());
	if(!m_elgamal.encode()){
		QMessageBox::warning(this, "Error", "Wrong Message Data");
	} else {
		ui->m_elGamalEncodedMessage->setText(QString::fromStdWString(m_elgamal.getEncodedMessage()));
	}
}

void MainWindow::elgamalDecode()
{
	QString str = ui->m_elGamalPLine->text();
	if(!str.size()){
		QMessageBox::warning(this, "Error", "Wrong P");
		return;
	}
	m_elgamal.setP(str.toInt());
	str = ui->m_elGamalGLine->text();
	if(!str.size()){
		QMessageBox::warning(this, "Error", "Wrong G");
		return;
	}
	m_elgamal.setG(str.toInt());
	str = ui->m_elGamalEncodedMessage->toPlainText();
	m_elgamal.setEncodedMessage(str.toStdWString());
	if(!m_elgamal.decode()){
		QMessageBox::warning(this, "Error", "Wrong Message Data");
	} else {
		ui->m_elGamalDecodedMessage->append(QString::fromStdWString(m_elgamal.getDecodedMessage()));
	}
}

void MainWindow::RSAEncode()
{
	std::string message = ui->m_RSAMessage->toPlainText().toStdString();
	m_rsa.setMessage(message);
	m_rsa.encode();
	std::list<types::ull> res = m_rsa.getEncodedMessage();
	QString result;
	for(auto it: res){
		result += QString::number(it);
	}

	ui->m_RSAEncoded->setText(result);
	ui->m_RSADecode->setEnabled(true);
}

void MainWindow::RSADecode()
{
	m_rsa.decode();
	std::string result = m_rsa.getDecodedMessage();

	ui->m_RSADecoded->setText(QString(result.c_str()));
}


void MainWindow::initTabs()
{
	ui->m_RSADecode->setEnabled(false);
	ui->m_gronsfeldCipherLine->setValidator(new QIntValidator(0, std::numeric_limits<int>::max(), this));
	std::pair<types::ull, types::ull> publicKey = m_rsa.getPublicKey();
	std::pair<types::ull, types::ull> privateKey = m_rsa.getPrivateKey();
	std::pair<types::ull, types::ull> pq = m_rsa.getPQ();

	ui->m_pLine->setText(QString::number(pq.first));
	ui->m_qLine->setText(QString::number(pq.second));

	ui->m_eLine->setText(QString::number(publicKey.first));
	ui->m_nLine->setText(QString::number(publicKey.second));

	ui->m_dLine->setText(QString::number(privateKey.first));
	ui->m_nLine_2->setText(QString::number(privateKey.second));

	setButtons();
}
