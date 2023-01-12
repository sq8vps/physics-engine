#include "common.hpp"
#include <cstdlib>

float randf(float min, float max)
{ 
    return min + static_cast <float>(std::rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}