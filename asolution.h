#ifndef ASOLUTION_H
#define ASOLUTION_H

#include "aelement.h"

template <class AElement, int num_elements>
class ASolution
{
public:
    //ASolution();

protected:
    virtual void mutate() = 0;
};

#endif // ASOLUTION_H
