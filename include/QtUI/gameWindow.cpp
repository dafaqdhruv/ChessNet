#include <QApplication>

#include "gameWindow.hpp"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	gameWindow mainWindow;
#ifdef Q_OS_ANDROID
	mainWindow.showMaximized();
#else
	mainWindow.show();
#endif

	return app.exec();
}

