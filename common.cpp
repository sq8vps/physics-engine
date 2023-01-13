#include "common.hpp"
#include <cstdlib>

float randf(float min, float max)
{ 
    return min + static_cast <float>(std::rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

float sgn(float val) 
{
    if(val < 0.f)
        return -1.f;
    else if(val > 0.f)
        return 1.f;
    
    return 0.f;
}