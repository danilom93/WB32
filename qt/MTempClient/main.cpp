#include "MTempClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MTempClient w;

    a.setApplicationName("MTempClient");
    a.setApplicationVersion("1.0");
    a.setOrganizationName("Unikore");
    a.setOrganizationDomain("www.unikore.it");

    w.show();

    return a.exec();
}
