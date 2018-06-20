#include <QApplication>
#include <QIcon>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("RomAnalyze");
    app.setOrganizationName("RomAnalyze");
    MainWindow *mainWin = new MainWindow;
    mainWin->show();

    return app.exec();
}
