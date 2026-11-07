#include <QApplication>
#include <QStyleFactory>
#include "ClientWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // QStyle *fusion = QStyleFactory::create("Fusion");
    // app.setStyle(fusion);
    // app.setPalette(fusion->standardPalette());

    ClientWindow window;
    window.resize(450, 180);
    window.setWindowTitle("Клиент отправки файлов");
    window.show();

    return app.exec();
}