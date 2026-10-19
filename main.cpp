#include <QApplication>
#include <QPushButton>
#include <QToolBar>
#include <QMainWindow>
#include <QStyle>
#include "StateButton.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.resize(300,400);

    QToolBar *toolbar = mainWindow.addToolBar("Main toolbar");

    StateButton *stateButton = new StateButton(&mainWindow);
    
    //иконки с tabler.io/icons
    QIcon onIcon(":/icons/lock_closed.png");
    QIcon offIcon(":/icons/lock_open.png");

    stateButton->setOnIcon(onIcon);
    stateButton->setOffIcon(offIcon);

    toolbar->addWidget(stateButton);

    mainWindow.show();

    return app.exec();
}