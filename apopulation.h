#ifndef APOPULATION_H
#define APOPULATION_H

#include "asolution.h"


// Will it figure behaviour of ASolution?
template <class ASolution, int num_slns>
class APopulation
{
public:
    //APopulation(const cv::Mat& img) {};  // -- though I could inherit
    //APopulation();
/*
    APopulation(int);
    APopulation(const APopulation&);
*/
    virtual void mutate_all() = 0;
    virtual void crossover() = 0;
private:

};

#endif // APOPULATION_H
