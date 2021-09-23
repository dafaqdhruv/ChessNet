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

class Dialog : public QDialog
{
    Q_OBJECT

public:
	Dialog()
	{
	    createFormGroupBox();

	    connectButton = new QPushButton("&Connect", this);
	    connectButton -> setAutoDefault(true);
	    connectButton -> setMaximumWidth(70);

	    connect(connectButton, &QPushButton::clicked, this, &Dialog::getIP6);

	    QVBoxLayout *mainLayout = new QVBoxLayout;

	    mainLayout->addWidget(formGroupBox);
	    mainLayout->addSpacing(5);
	    mainLayout->addWidget(connectButton, 0, Qt::AlignRight);

	    setLayout(mainLayout);

	    setWindowTitle(tr("Connect to Server"));
	    setMinimumSize(360, 135);
	    setMaximumSize(360, 135);
	}

	std::string exportIP6()
	{
		return ipAddress.toString().toStdString();
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
				std::cout<<exportIP6()<<std::endl;
			}
			else {
				continueBox.reject();
			}
		}
	}
};

#endif // DIALOG_H
