#include "showimageqt5dialog.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    showimageqt5Dialog w;
    w.show();

    return a.exec();
}
