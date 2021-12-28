#include <QApplication>

#include "../include/setupServer.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Dialog dialog;

    //QObject::connect(&dialog, &askMediumDialog::medium, [](const bool ret){
    QObject::connect(&dialog, &Dialog::exportScrambler, [](const std::string ret){std::cout<<ret<<std::endl;  });
#ifdef Q_OS_ANDROID
    dialog.showMaximized();
#else
    dialog.show();
#endif

    return app.exec();
}
