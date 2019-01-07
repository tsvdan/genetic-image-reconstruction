#include "ellipse.h"

Ellipse::Ellipse(const std::array<int, 7>& ar) {
    x = ar[0];
    y = ar[1];
    major_ax = ar[2];
    minor_ax = ar[3];
    angle = ar[4];
    thickness = ar[5];
    color = ar[6];
}

Ellipse::Ellipse(const cv::Mat& img) :
    x(randint(0, img.cols)),
    y(randint(0, img.rows)),
    major_ax(randint(10, std::max(img.rows, img.cols) / 2)),
    minor_ax(randint(5, std::max(img.cols, img.rows) / 2)),
    angle(randint(0, 360)),
    thickness(1),
    color(randint(10, 255))
{}

void Ellipse::draw(cv::Mat& img) const {
    cv::ellipse(img, cv::Point(x, y), cv::Size(major_ax, minor_ax),
                angle, START_ANGLE, END_ANGLE,
                cv::Scalar(color));
}


std::array<int, 7> Ellipse::to_array() const {
    std::array<int, 7> ar{0};  // should be { 0, 0, ...}
    ar[0] = x;
    ar[1] = y;
    ar[2] = major_ax;
    ar[3] = minor_ax;
    ar[4] = angle;
    ar[5] = thickness;
    ar[6] = color;
    return ar;
}

void Ellipse::mutate() {
    // nothing yet
}
