#ifndef DIALOG_H
#define DIALOG_H

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
	ClientConnect()
	{
		createFormGroupBox();

		connectButton = new QPushButton("&Connect", this);
		connectButton -> setAutoDefault(true);
		connectButton -> setMaximumWidth(70);

		connect(connectButton, &QPushButton::clicked, this, &ClientConnect::getIP6);
		connect(this, &ClientConnect::exportIP6, this, &QDialog::accept);

		QVBoxLayout *getIPLayout = new QVBoxLayout;

		getIPLayout->addWidget(formGroupBox);
		getIPLayout->addSpacing(5);
		getIPLayout->addWidget(connectButton, 0, Qt::AlignRight);

		setLayout(getIPLayout);

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
			}
			else {
				continueBox.reject();
			}
		}
	}

signals:
	void exportIP6(const std::string &IP);
};

class GameDialog : public QDialog
{
    Q_OBJECT

public:
	GameDialog()
	{
		continueButton = new QPushButton("&Continue", this);
		continueButton -> setAutoDefault(true);
		continueButton -> setMaximumWidth(70);

		connect(continueButton, &QPushButton::clicked, this, &GameDialog::getRadio);
		connect(this, &GameDialog::medium, this, &QDialog::accept);

		QVBoxLayout *gameDialogLayout = new QVBoxLayout;

		client = new QRadioButton("Client", this);
		server = new QRadioButton("Server", this);

		gameDialogLayout -> addWidget(client, 50, Qt::AlignCenter);
		gameDialogLayout -> addSpacing(10);
		gameDialogLayout -> addWidget(server, 50, Qt::AlignCenter);
		gameDialogLayout -> addSpacing(10);
		gameDialogLayout -> addWidget(continueButton, 0, Qt::AlignRight);

		setLayout(gameDialogLayout);

		setWindowTitle(tr("ChessNet"));
		setMinimumSize(200, 130);
		setMaximumSize(200, 130);
	}

	virtual ~GameDialog(){}

signals:
	void medium (const bool &ret);
private:
	QRadioButton *client;
	QRadioButton *server;
	QPushButton *continueButton;
	bool makeServer;
	bool makeClient;

	void getRadio(){
		makeServer = server->isChecked();
		makeClient = client->isChecked();

		if(makeServer ^ makeClient) {
			emit medium(makeServer);
		}
		else {
			QMessageBox errorBox;
			errorBox.setText("Make a choice.");
			errorBox.exec();
		}
	}
};

#endif // DIALOG_H
