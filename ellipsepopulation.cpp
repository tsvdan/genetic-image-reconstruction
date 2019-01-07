#include "ellipsepopulation.h"

template <int num_elements, int num_slns>
void EllipsePopulation<num_elements, num_slns>::crossover() {
    // nothing
}

    
template <int num_elements, int num_slns>
void EllipsePopulation<num_elements, num_slns>::mutate_all() {
    for (auto member : population)
        member.mutate();
}
