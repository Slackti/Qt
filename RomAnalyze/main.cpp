#include <QApplication>
#include <QIcon>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("QHexEdit2");
    app.setOrganizationName("QHexEdit2");
    MainWindow *mainWin = new MainWindow;
    mainWin->show();

    return app.exec();
}
