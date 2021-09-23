#include <QApplication>

#include "setupServer.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Dialog dialog;
#ifdef Q_OS_ANDROID
    dialog.showMaximized();
#else
    dialog.show();
#endif

    return app.exec();
}
