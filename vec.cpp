#include "vec.hpp"

std::ostream& operator<<(std::ostream &o, const Vec3 &v)
{
    o << "x=" << v.x << " y=" << v.y << " z=" << v.z;
    return o;
}