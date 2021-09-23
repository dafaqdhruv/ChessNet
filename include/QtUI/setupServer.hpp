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
	    scrambler = "";

	    continueButton = new QPushButton("&Continue", this);
	    continueButton -> setAutoDefault(true);
	    continueButton -> setMaximumWidth(70);
	    connect(continueButton, &QPushButton::clicked, this, &Dialog::getScrambler);

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

	std::string exportscrambler()
	{
		return scrambler;
	}

private:
	QLineEdit *scramblerLineEdit;
	QPushButton *continueButton;
	QHostAddress ipAddress;
	std::string  scrambler;

    	void getScrambler(){
		scrambler = scramblerLineEdit->displayText().toStdString();
	}
};

#endif // DIALOG_H
