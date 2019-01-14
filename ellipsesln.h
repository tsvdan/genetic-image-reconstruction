#ifndef ELLIPSESLN_H
#define ELLIPSESLN_H
#include "ellipse.h"
#include "asolution.h"

template <int num_elements>
class EllipseSln : ASolution<Ellipse, num_elements> {
public:
    EllipseSln();
    ~EllipseSln() {  }            // should delete[] elements 
    EllipseSln(const cv::Mat&);  // random constructor
    EllipseSln(const EllipseSln& rhs)
        : elements(rhs.elements)
        , _image(rhs._image)
        , _temp(rhs._temp)
    {}
    EllipseSln<num_elements>& operator=(const EllipseSln<num_elements>& pop) {
        for (int i = 0; i < num_elements; ++i)
            this->elements[i] = pop.elements[i];
        this->_image = pop._image;
        this->_temp = pop._temp;
        return *this;
    } // pop's _image's are not accessible
    EllipseSln<num_elements>& operator=(const EllipseSln<num_elements>&& pop) {
        for (int i = 0; i < num_elements; ++i)
            this->elements[i] = pop.elements[i];
        this->_image = pop._image;
        this->_temp = pop._temp;
        return *this;
    }

    mutable std::vector<Ellipse> elements;  // or at least pointers
    mutable cv::Mat _image{cv::Mat::zeros(1, 1, CV_8UC3)};
    mutable cv::Mat _temp{cv::Mat::zeros(1, 1, CV_8UC3)};


    void mutate() override;
    void draw() const override;
    double fitness(const cv::Mat& original) const override;
private:

};

template <int n>
inline EllipseSln<n>::EllipseSln() {
    elements = std::vector<Ellipse>(n);
    std::cout << "New Ellipse Solution " << n << " constructed! " << std::endl;
}

template <int n>
inline EllipseSln<n>::EllipseSln(const cv::Mat& img) {
    img.copyTo(_image);  // these gotta be new
    img.copyTo(_temp);

    std::vector<Ellipse> aliments;
    aliments.reserve(n);
    for (int i = 0; i < n; ++i){
        aliments.emplace_back(Ellipse(_image));
    }
    elements = std::move(aliments);
    std::cout << "New Ellipse Solution "     << n
              << " constructed on cv::Mat! " << std::endl;
}

template <int n>
inline double EllipseSln<n>::fitness(const cv::Mat& original) const {
    double dist = cv::norm(_image - original, cv::NORM_L1);
    //_temp.copyTo(_image);
    if (dist == 0) {
        std::cout << cv::norm(_temp - original, cv::NORM_L1) << std::endl;
    }
    return 1e9 / (dist + 1e-6);
}

template <int n>
inline void EllipseSln<n>::draw() const {
    for (auto& e : elements) {
        e.draw(_image);
    }
}

template <int n>
inline void EllipseSln<n>::mutate() {
    for (auto& e : elements) {
        if (randint(1, 100) <= 15) e.mutate();
    }
}


#endif // ELLIPSESLN_H
