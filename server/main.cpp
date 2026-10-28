#include <QApplication>
#include <QStyleFactory>
#include "ServerWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ServerWindow window;
    window.resize(500,400);
    window.setWindowTitle("Сервер");
    window.show();

    return app.exec();
}