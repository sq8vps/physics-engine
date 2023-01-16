#include "vec.hpp"


/**
 * @brief Print vector to output stream 
**/
std::ostream& operator<<(std::ostream &o, const Vec3 &v)
{
    o << "x=" << v.x << " y=" << v.y << " z=" << v.z;
    return o;
}