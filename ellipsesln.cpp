#include "ellipsesln.h"

/*
template <int n>
EllipseSln<n>::EllipseSln() {
    elements = new Ellipse[n];
    std::cout << "New Ellipse Solution " << n << " constructed! " << std::endl;
}

template <int n>
EllipseSln<n>::EllipseSln(const cv::Mat& img) {
    elements = new Ellipse[n];
    for (auto e : elements)
        e = Ellipse(img);
    std::cout << "New Ellipse Solution "     << n
              << " constructed on cv::Mat! " << std::endl;
}

template <int num_elements>
void EllipseSln<num_elements>::mutate() {
    for (auto e : elements) e.mutate();
}

template <int num_elements>
EllipseSln<num_elements>::EllipseSln(const cv::Mat& img) {
    //std::array<Ellipse, n> ar;
    for (int i = 0; i < num_elements; ++i) {
        elements[i] = Ellipse(img);
    }
    //elements = ar;  // will this work?

    //std::array<Ellipse, n> 
    //this->elements = ar;
}
*/
