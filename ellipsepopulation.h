#ifndef ELLIPSEPOPULATION_H
#define ELLIPSEPOPULATION_H

#include "apopulation.h"
#include "ellipsesln.h"

template <int num_elements, int num_slns>
class EllipsePopulation : APopulation<EllipseSln<num_elements>, num_slns>
{
public:
    EllipsePopulation();  // :ui(...) part of constructor fails w/o
    // now also an undefined reference
    
    EllipsePopulation(const cv::Mat& img) {
        for (int i = 0; i < num_slns; ++i) {
            population[i] = EllipseSln<num_elements>(img);
        }
    }
    void populate(const cv::Mat& img) {
        for (int i = 0; i < num_slns; ++i) {
            population[i] = EllipseSln<num_elements>(img);
        }
    }

    EllipsePopulation<num_elements, num_slns>& operator=(EllipsePopulation<num_elements, num_slns>&& pop) {
        this->population = pop.population;
        return *this;
    }

protected:
    void crossover() override;  
    void mutate_all() override;
    std::array<EllipseSln<num_elements>, num_slns> population;
};


#endif // ELLIPSEPOPULATION_H
