#ifndef AELEMENT_H
#define AELEMENT_H

#include <opencv2/opencv.hpp>
#include <array>

template <int coords>
class AElement
{
public:
    //AElement();
    virtual void draw(cv::Mat&) const = 0;
    virtual void mutate() = 0;
    virtual std::array<int, coords> to_array() const = 0;
};

#endif // AELEMENT_H
