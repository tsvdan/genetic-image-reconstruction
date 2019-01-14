#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui = new Ui::MainWindow;
    ui->setupUi(this);

    // Image Processing
    original_full_resolution = cv::imread("/home/pupof/Pictures/lower_right_circle.jpg", cv::IMREAD_GRAYSCALE);
    cv::cvtColor(original_full_resolution, original_resized, cv::COLOR_GRAY2RGB);

    /* Set up Mat to be displayed */
    // should resize to some internal resoultion for computation
    cv::resize(original_resized, original_resized, cv::Size(ui->left_label->width(), ui->left_label->height()));
    imgq_right = QImage(original_resized.data, original_resized.cols,
        original_resized.rows, original_resized.cols*3, QImage::Format_RGB888);
    ui->right_label->setPixmap(QPixmap::fromImage(imgq_right));

    /* -- Ellipse Solutions. Init -- */
    blank_canvas = cv::Mat::zeros(original_resized.rows, original_resized.cols, CV_8UC3);
    EllipsePopulation<100, 50> pop(original_resized.clone()); // mutates?
    population = pop;

    // replace with concurrency
    // HOW TO RUN COMPUTATION?
    //  * time for one mutation?
    //  * stack drawings and constantly compute
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(temp_func()));
    timer->start(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// for deprecation
void MainWindow::temp_func() {
    population.selection(original_resized);
// Calculate (& Display) Statistics
    ui->acc_lbl->setText(QString::number(population.population[population.population.size() - 1].fitness(original_resized), 'f', 5));
//
    blank_canvas = population.draw_best();

/*  --  Separate logic  --  */
    // Display Evolving Picture
    imgq_left = QImage(blank_canvas.data, blank_canvas.cols,
                       blank_canvas.rows, blank_canvas.cols,  // bytesperline
                       QImage::Format_Grayscale8);
    ui->left_label->setPixmap(QPixmap::fromImage(imgq_left));

}

void MainWindow::test_func() {
    EllipseSln<5> sln(blank_canvas);
    sln.draw();
    sln.fitness(original_resized);
    blank_canvas = sln._image;

    std::cout << sln.fitness(original_resized) << std::endl;





    imgq_left = QImage(blank_canvas.data, blank_canvas.cols,
                       blank_canvas.rows, blank_canvas.cols,  // bytesperline
                       QImage::Format_Grayscale8);
    blank_canvas = sln._temp;

    ui->left_label->setPixmap(QPixmap::fromImage(imgq_left));

    // Calculate (& Display) Statistics
    ui->acc_lbl->setText(QString::number(sln.fitness(original_resized), 'f', 5));
}


bool MainWindow::inrange(int val, int lower, int upper) {
    // lambdify
    return lower <= val && val <= upper;
}
