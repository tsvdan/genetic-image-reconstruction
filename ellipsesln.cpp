#include "ellipsesln.h"
/* 
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
template <int num_elements>
void EllipseSln<num_elements>::mutate() {
    for (auto e : elements)
        e.mutate();
}