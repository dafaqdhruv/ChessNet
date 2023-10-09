#ifndef DIALOG_H
#define DIALOG_H

#include <iostream>
#include <string>

#include <QtWidgets>
#include <QtNetwork/QHostAddress>
#include <QDialog>
#include <QErrorMessage>

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE

class ClientConnect : public QDialog
{
    Q_OBJECT

public:
	clientConnect()
	{
		createFormGroupBox();

		connectButton = new QPushButton("&Connect", this);
		connectButton -> setAutoDefault(true);
		connectButton -> setMaximumWidth(70);

		connect(connectButton, &QPushButton::clicked, this, &ClientConnect::getIP6);

		QVBoxLayout *mainLayout = new QVBoxLayout;

		mainLayout->addWidget(formGroupBox);
		mainLayout->addSpacing(5);
		mainLayout->addWidget(connectButton, 0, Qt::AlignRight);

		setLayout(mainLayout);

		setWindowTitle(tr("Connect to Server"));
		setMinimumSize(360, 135);
		setMaximumSize(360, 135);
	}


private:
	QGroupBox *formGroupBox;
	QLineEdit *ipLineEdit;
	QPushButton *connectButton;
	QHostAddress ipAddress;
	void createFormGroupBox()
	{
		formGroupBox = new QGroupBox(tr("Server IP"));
		QFormLayout *layout = new QFormLayout;

		ipLineEdit = new QLineEdit("", this);
		ipLineEdit -> setFrame(true);
		ipLineEdit -> setMaxLength(46);
		// 	Not required anymore;
		// 	QHostAddress::isNull does the job
		//	ipLineEdit -> setInputMask("000.000.000.000;0");
		layout->addRow(new QLabel(tr("Enter IPV6 address :")), ipLineEdit);

		formGroupBox->setLayout(layout);
	}

	void getIP6(){

		ipAddress = QHostAddress(ipLineEdit->displayText());

		if(ipAddress.isNull()){
			QMessageBox errorBox;
			errorBox.setText("Invalid IP Address.");
			errorBox.exec();
		} else {

			QMessageBox continueBox;
			continueBox.setText("IP address is valid. Are you sure you want to connect to this host?");

			QPushButton *yesButton = continueBox.addButton("&Yes", QMessageBox::YesRole);
			QPushButton *noButton = continueBox.addButton("&No", QMessageBox::NoRole);
			continueBox.exec();

			if (continueBox.clickedButton() == yesButton){
				emit exportIP6(ipAddress.toString().toStdString());
				//std::cout<<exportIP6()<<std::endl;
			}
			else {
				continueBox.reject();
			}
		}
	}
signals :
	void exportIP6(const std::string &IP);
};

class setupServer : public QDialog
{
    Q_OBJECT

public:
	setupServer()
	{
		scrambler = "";

		continueButton = new QPushButton("&Continue", this);
		continueButton -> setAutoDefault(true);
		continueButton -> setMaximumWidth(70);
		connect(continueButton, &QPushButton::clicked, this, &setupServer::getScrambler);

		scramblerLineEdit = new QLineEdit("", this);
		scramblerLineEdit -> setMaxLength(10);
		scramblerLineEdit -> setMaximumWidth(95);

		QVBoxLayout *mainLayout = new QVBoxLayout;

		mainLayout -> addWidget(new QLabel("Enter scrambler value :"));
		mainLayout -> addSpacing(10);
		mainLayout -> addWidget(scramblerLineEdit, 0, Qt::AlignCenter);
		mainLayout -> addSpacing(10);
		mainLayout -> addWidget(continueButton, 0, Qt::AlignRight);

		setLayout(mainLayout);

		setWindowTitle(tr("Setup Scrambler"));
		setMinimumSize(200, 130);
		setMaximumSize(200, 130);
	}

signals: void exportScrambler(const int out);
private:
	QLineEdit *scramblerLineEdit;
	QPushButton *continueButton;
	QHostAddress ipAddress;
	std::string  scrambler;

	void getScrambler(){
		scrambler = scramblerLineEdit->displayText().toStdString();
		if(scrambler.length()){
			emit exportScrambler(std::stoi(scrambler));
		}
	}
};


class askMediumDialog : public QDialog
{
    Q_OBJECT

public:
	askMediumDialog()
	{

		continueButton = new QPushButton("&Continue", this);
		continueButton -> setAutoDefault(true);
		continueButton -> setMaximumWidth(70);
		connect(continueButton, &QPushButton::clicked, this, &askMediumDialog::getRadio);
		QObject::connect(continueButton, SIGNAL(clicked()), this, SLOT(accept()));
		QVBoxLayout *mainLayout = new QVBoxLayout;

		client = new QRadioButton("Client", this);
		server = new QRadioButton("Server", this);
		mainLayout -> addWidget(client, 50, Qt::AlignCenter);
		mainLayout -> addSpacing(10);
		mainLayout -> addWidget(server, 50, Qt::AlignCenter);
		mainLayout -> addSpacing(10);
		mainLayout -> addWidget(continueButton, 0, Qt::AlignRight);

		setLayout(mainLayout);

		setWindowTitle(tr("Setup Scrambler"));
		setMinimumSize(200, 130);
		setMaximumSize(200, 130);
	}

signals:
	void medium (const bool ret);
private:
	QRadioButton *client;
	QRadioButton *server;
	QPushButton *continueButton;
	bool makeServer;
	bool makeClient;

	void getRadio(){
		makeServer = server->isChecked();
		makeClient = client->isChecked();
		if(makeServer ^ makeClient){

			emit medium(makeServer);			// emit signal for choice
		}
		else {
			QMessageBox errorBox;
			errorBox.setText("Make a choice.");
			errorBox.exec();
		}
	}
};


#endif // DIALOG_H
