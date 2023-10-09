#include <QApplication>

#include "../include/clientConnect.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ClientConnect dialog;

    QObject::connect(&dialog, &ClientConnect::exportIP6,[](const std::string ip){std::cout<<ip<<" okay this.\n";});
    dialog.show();

    return app.exec();
}
