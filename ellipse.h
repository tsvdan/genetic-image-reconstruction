#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "aelement.h"
#include <algorithm>
#include <experimental/random>

// change to forward-declare randint
using  std::experimental::fundamentals_v2::randint;


class Ellipse : public AElement<7>
{
public:
    Ellipse() : Ellipse(cv::Mat::zeros(100, 100, CV_8UC3)) {}
    Ellipse(const cv::Mat&);
    Ellipse(const std::vector<int>&);

    Ellipse(const Ellipse& elly) :
        x(elly.x),
        y(elly.y),
        major_ax(elly.major_ax),
        minor_ax(elly.minor_ax),
        angle(elly.angle),
        color(elly.color),
        thickness(elly.thickness),
        _ROWS(elly._ROWS),
        _COLS(elly._COLS)
    {}

    Ellipse& operator=(const Ellipse& elly) {
        x = elly.x;
        y = elly.y;
        major_ax = elly.major_ax;
        minor_ax = elly.minor_ax;
        angle = elly.angle;
        color = elly.color;
        thickness = elly.thickness;
        _ROWS = elly._ROWS;
        _COLS = elly._COLS;
        return *this;
    }

    static void crossover(Ellipse& el, Ellipse& ly) {
/*        using std::swap;

        swap(el.y, ly.y);
        if (randint(0, 100) < 50) {
            swap(el.major_ax, ly.major_ax);
        } else {
            swap(el.minor_ax, ly.minor_ax);
        }
*/
    }

    void draw(cv::Mat&) const override;
    std::vector<int> to_vector() const override;

    Ellipse& operator=(Ellipse& elly) {
        return elly;
    }
    void mutate() override;

private:
    int x{0};
    int y{0};
    int major_ax{75};
    int minor_ax{50};
    int angle{0};
    int color{127};   // b/w intensity
    // color should really be a cv::Scalar, but who cares
    int thickness{cv::FILLED};


    const int START_ANGLE{0};
    const int END_ANGLE{360};

public:

    int _ROWS;  // population on w doesn't get init
    int _COLS;

};

#endif // ELLIPSE_H
