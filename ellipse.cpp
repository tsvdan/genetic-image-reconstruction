#include "ellipse.h"

Ellipse::Ellipse(const std::vector<int>& ar) {
    x = ar[0];
    y = ar[1];
    major_ax = ar[2];
    minor_ax = ar[3];
    angle = ar[4];
    color = ar[6];
    thickness = ar[5];
}

Ellipse::Ellipse(const cv::Mat& img) :
    x(randint(0, img.cols)),
    y(randint(0, img.rows)),
    major_ax(randint(1, std::max(img.rows, img.cols) / 2)),
    minor_ax(randint(1, std::max(img.cols, img.rows) / 2)),
    angle(randint(0, 360)),
    color(randint(0, 255)),
    _ROWS(img.rows),
    _COLS(img.cols)
{}

void Ellipse::draw(cv::Mat& img) const {
    cv::ellipse(img, cv::Point(x, y), cv::Size(major_ax, minor_ax),
                angle, START_ANGLE, END_ANGLE,
                cv::Scalar(color), thickness);
}


std::vector<int> Ellipse::to_vector() const {
    std::vector<int> ar(7);  // should be { 0, 0, ...}
    ar[0] = x;
    ar[1] = y;
    ar[2] = major_ax;
    ar[3] = minor_ax;
    ar[4] = angle;
    ar[6] = color;
    ar[5] = thickness;
    return ar;
}

void Ellipse::mutate() {
    auto saturate = [](int val, int lower_b, int higher_b) -> int {
        if (val < lower_b) return lower_b;
        if (val > higher_b) return higher_b;
        return val;
    };
    auto evariate =
            [&](int val, int var, int prob, int lower_b, int higher_b) -> int {
        if (randint(0, 100) < prob)
            return saturate(val + var, lower_b, higher_b);
        return saturate(val - var, lower_b, higher_b);
    };

    major_ax = evariate(major_ax, 1 + major_ax / 10, 50, 1, std::max(_ROWS, _COLS) / 2);
    minor_ax = evariate(minor_ax, 1 + minor_ax / 10, 50, 1, major_ax);
    x = evariate(x, _ROWS / 10, 50, 0, _ROWS + major_ax);
    y = evariate(y, _COLS / 10, 50, 0, _COLS + major_ax);
    angle = evariate(angle, 5, 50, 0, 360);
    color = evariate(color, 40, 50, 0, 255);

}
