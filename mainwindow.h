#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <iostream>
#include <opencv2/core.hpp>
#include <experimental/random>
#include "ellipsepopulation.h"

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
    void test_func();
    //void ellipse_sln();

private:
    Ui::MainWindow *ui;
    cv::Mat original_full_resolution;
    cv::Mat original_resized;
    cv::Mat displayed_resized;
    cv::Mat blank_canvas;
    cv::Mat displayed_canvas;
    //cv::Mat img;
    QImage imgq_right;
    QImage imgq_left;
    //EllipsePopulation<30, 50> population;  // fuck me
    // sort() dominates complexity (mb even .fitness())
    EllipsePopulation<100, 50> population;

    bool inrange(int, int, int);
};

#endif // MAINWINDOW_H
