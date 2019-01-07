#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui = new Ui::MainWindow;
    ui->setupUi(this);

    // Image Processing
    original = cv::imread("/home/pupof/Pictures/google-earth-view-2433.jpg", cv::IMREAD_GRAYSCALE);
    cv::cvtColor(original, original, cv::COLOR_GRAY2RGB); // or gray2rgb
    img = cv::Mat::zeros(original.rows, original.cols, CV_8UC3);

    // Set up Mat to be displayed
    cv::Mat resized_img;
    cv::resize(original, resized_img, cv::Size(ui->left_label->width(), ui->left_label->height()));
    imgq = QImage(resized_img.data, resized_img.cols, resized_img.rows, resized_img.cols*3, QImage::Format_RGB888);
    // Display Mat as a Label
    ui->right_label->setPixmap(QPixmap::fromImage(imgq));

    /* -- Ellipse Solutions. Init -- */
    //population.populate(img);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(temp_func())); // replace with concurrency
    timer->start(80);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// for deprecation
void MainWindow::temp_func() {
    // faster with pointers
    cv::Mat copy_img{img};
    /*
    for (int i = 0; i < ellipse_array.size(); ++i) {
        if (randint(0, 100) < 50) {
            // mutate + draw on img
            std::array<uint16_t, 5> _temp{ellipse_array[i]}; // should copy array
            _temp[0] += 20;
            _temp[1] -= 20;
            _temp[2] += 10;
            _temp[3] -= 10;
            ellipse_array[i] = _temp;
        }
        cv::ellipse(copy_img,
            cv::Point(ellipse_array[i][0], ellipse_array[i][1]),
            cv::Size(ellipse_array[i][2], ellipse_array[i][3]),
            ellipse_array[i][4], 0, 360,
            cv::Scalar(ellipse_array[i][4]));

    }
    */
    /* // This is fine
    Ellipse e(img);
    e.draw(img);
    */
    // Is this?
    EllipseSln<1> sln(img);
    for (auto e: sln.elements) e.draw(img);

    // Display Evolving Picture
    cv::Mat resized_img;
    cv::resize(copy_img, resized_img, cv::Size(ui->left_label->width(), ui->left_label->height()));
    imgq = QImage(resized_img.data, resized_img.cols, resized_img.rows, resized_img.cols*3, QImage::Format_Grayscale8);
    ui->left_label->setPixmap(QPixmap::fromImage(imgq));
    //this->repaint();

    // Calculate (& Display) Statistics
    ui->acc_lbl->setText(QString::number(MSE(copy_img, original), 'f', 2));
}

double MainWindow::MSE(const cv::Mat& m1, const cv::Mat& m2) {
    cv::Mat diff_array;
    cv::absdiff(m1, m2, diff_array);
    //cv::pow(diff_array, 2.0, diff_array);
    cv::Scalar reduced_diff = cv::mean(diff_array);

    //qDebug
    //qDebug << reduced_diff;  // also doesn't work
    return reduced_diff.val[0];
}

bool MainWindow::inrange(int val, int lower, int upper) {
    // lambdify
    return lower <= val && val <= upper;
}
