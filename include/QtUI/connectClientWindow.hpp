#ifndef DIALOG_H
#define DIALOG_H

#include <string>

#include <QtWidgets>
#include <QDialog>


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
		return ipAddress.toStdString();
	}

private:
	QGroupBox *formGroupBox;
	QLineEdit *ipLineEdit;
	QPushButton *connectButton;
	QString ipAddress = "";
	void createFormGroupBox()
	{
	    formGroupBox = new QGroupBox(tr("Server IP"));
	    QFormLayout *layout = new QFormLayout;

	    ipLineEdit = new QLineEdit("  :  :  :  :  ", this);
	    ipLineEdit -> setFrame(true);
	    ipLineEdit -> setMaxLength(46);

	    layout->addRow(new QLabel(tr("Enter IPV6 address :")), ipLineEdit);

	    formGroupBox->setLayout(layout);
	}

    	void getIP6(){
		
		ipAddress = ipLineEdit->displayText();
	}
};

#endif // DIALOG_H
