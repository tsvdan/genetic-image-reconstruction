#ifndef ELLIPSESLN_H
#define ELLIPSESLN_H
#include "ellipse.h"
#include "asolution.h"

template <int num_elements>
class EllipseSln : ASolution<Ellipse, num_elements> {
public:
    EllipseSln(const cv::Mat&);  // random constructor
    //EllipseSln(const EllipseSln&);  
    EllipseSln<num_elements>& operator=(EllipseSln<num_elements>&& pop) {
        for (int i = 0; i < num_elements; ++i)
            this->elements[i] = pop.elements[i];
        return *this;
    }

    std::array<Ellipse, num_elements> elements;
    
protected:
    void mutate() override;

};

template <int num_elements>
inline EllipseSln<num_elements>::EllipseSln(const cv::Mat& img) {
    //std::array<Ellipse, n> ar;
    for (int i = 0; i < num_elements; ++i) {
        Ellipse e(img);
        elements[i] = e;
    }
    //elements = ar;  // will this work?

    //std::array<Ellipse, n> 
    //this->elements = ar;
}

#endif // ELLIPSESLN_H
