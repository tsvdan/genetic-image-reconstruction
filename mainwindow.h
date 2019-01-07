#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <iostream>
#include <opencv2/core.hpp>
#include <experimental/random>
#include "ellipsepopulation.h"
/* // Defined in ellipse, which is included in ellipsesln
#include <array>
#include <opencv2/opencv.hpp>
 */
using std::experimental::fundamentals_v2::randint;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void temp_func();
    //void ellipse_sln();

private:
// dunno, if Polevoy will be furious for no RAII (no?)
    Ui::MainWindow *ui;
    cv::Mat original;
    cv::Mat img;        // current iterated/displayed image
    QImage imgq;        // used to display the images (should really be local to main()/constructor)
    //EllipsePopulation<30, 50> population;  // fuck me

    double MSE(const cv::Mat&, const cv::Mat&);
    bool inrange(int, int, int);
};

#endif // MAINWINDOW_H
