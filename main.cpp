#include "calculator.h"
#include <QApplication>
//#include <QtPlugin>
//Q_IMPORT_PLUGIN (QWindowsIntegrationPlugin);
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator w;
    w.show();

    return a.exec();
}
