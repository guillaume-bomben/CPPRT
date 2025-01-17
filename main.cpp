//#include "mainwindow.h"
#include "tcpserverwindow.h"
#include "clientwindow.h"
//#include "registrationserver.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    //RegistrationServer server;

    TcpServerWindow serverWindow;
    serverWindow.show();

    ClientWindow w;
    w.show();

    ClientWindow a;
    a.show();

    return app.exec();
}

