#ifndef AELEMENT_H
#define AELEMENT_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

template <int coords>
class AElement
{
public:
    //AElement();
    virtual void draw(cv::Mat&) const = 0;
    virtual void mutate() = 0;
    virtual std::vector<int> to_vector() const = 0;
};

#endif // AELEMENT_H
