#include "mainwindow.h"
#include "imshow.h"
#include <QApplication>
#include <QImage>

using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //ImageShow();

    return a.exec();
}
