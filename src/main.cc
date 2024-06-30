#include "view/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model mod;
    Controller controller(&mod);
    MainWindow w(&controller);
    mod.AddObserver(&w);
    w.show();
    return a.exec();
}
