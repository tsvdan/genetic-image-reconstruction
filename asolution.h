#ifndef ASOLUTION_H
#define ASOLUTION_H

#include "aelement.h"

template <class AElement, int num_elements>
class ASolution
{
public:
    //ASolution();

    virtual void mutate() = 0;
    virtual void draw() const = 0;

    // figure the specifiers
    virtual double fitness(const cv::Mat& original) const = 0;
protected:
};

#endif // ASOLUTION_H
