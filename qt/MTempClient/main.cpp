#include "MTempClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MTempClient w;
    w.show();

    return a.exec();
}
