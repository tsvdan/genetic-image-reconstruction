#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "aelement.h"
#include <algorithm>
#include <experimental/random>

// change to forward-declare randint
using  std::experimental::fundamentals_v2::randint;

/*
class Mat;

// alternate representation
template <typename T, int n>
class array;
 */
class Ellipse : public AElement<7>
{
public:
    Ellipse();
    Ellipse(const cv::Mat&);
    Ellipse(const std::array<int, 7>&);
    void draw(cv::Mat&) const override;
    std::array<int, 7> to_array() const override;

    Ellipse& operator=(Ellipse& pop) {
        x = pop.x;
        y = pop.y;
        major_ax = pop.major_ax;
        minor_ax = pop.minor_ax;
        angle = pop.angle;
        thickness = pop.thickness;
        color = pop.color;
        return *this;
    }

protected:
    int x{0};
    int y{0};
    int major_ax{75};
    int minor_ax{50};
    int angle{0};
    int thickness{1};
    int color{127};   // b/w intensity
    // color should really be a cv::Scalar, but who cares

    const int START_ANGLE{0};
    const int END_ANGLE{360};

    void mutate() override;

};

#endif // ELLIPSE_H