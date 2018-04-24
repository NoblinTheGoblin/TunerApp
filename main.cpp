//#include "lauaudioobject.h"
#include "qcustomplot.h"
#include "tunergui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TunerGUI w;
    w.show();
    return a.exec();
}
