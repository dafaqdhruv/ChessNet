#include <QApplication>

#include "clientConnect.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    clientConnect dialog;

    QObject::connect(&dialog, &clientConnect::exportIP6,[](const std::string ip){std::cout<<ip<<" okay this.\n";});
#ifdef Q_OS_ANDROID
    dialog.showMaximized();
#else
    dialog.show();
#endif

    return app.exec();
}
