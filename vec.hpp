#pragma once

#include <vector>
#include <cmath>

/**
 * @brief A 3D vector class
**/
class Vec3
{
public:
    float x;
    float y;
    float z;
    Vec3(float x = 0.f, float y = 0.f, float z = 0.f) 
    : x(x), y(y), z(z) {}

    /**
     * @brief Push this vector to specified std::vector<float>
     * @param &dest Destination std::vector
    */
    void pushTo(std::vector<float> &dest)
    {
        dest.push_back(x);
        dest.push_back(y);
        dest.push_back(z);
    }

    /**
     * @brief Multiply vector by a constant
     * @param k Constant
     * @return Multiplied vector 
    **/
    Vec3 operator * (float k) const
    {
        Vec3 ret;
        ret.x = x * k;
        ret.y = y * k;
        ret.z = z * k;
        return ret;
    }

    /**
     * @brief Divide vector by a constant
     * @param k Constant
     * @return Divided vector 
    **/
    Vec3 operator / (float k) const
    {
        Vec3 ret;
        ret.x = x / k;
        ret.y = y / k;
        ret.z = z / k;
        return ret;
    }

    /**
     * @brief Subtract vectors
     * @param v Subtrahend
     * @return Subtracted vectors 
    **/
    Vec3 operator - (Vec3 v) const 
    {
        Vec3 ret;
        ret.x = x - v.x;
        ret.y = y - v.y;
        ret.z = z - v.z;
        return ret;
    }

     /**
     * @brief Add vectors
     * @param v 2nd vector
     * @return Added vectors 
    **/
    Vec3 operator + (Vec3 v) const 
    {
        Vec3 ret;
        ret.x = x + v.x;
        ret.y = y + v.y;
        ret.z = z + v.z;
        return ret;
    }

    /**
     * @brief Calculate cross-product of vectors
     * @param v 2nd factor
     * @return Cross-product of vectors
    **/
    Vec3 operator * (Vec3 v) const
    {
        Vec3 ret;
        ret.x = y * v.z - z * v.y;
        ret.y = z * v.x - x * v.z;
        ret.z = x * v.y - y * v.x;
        return ret;
    }

    /**
     * @brief Get vector length
     * @return Vector length
    **/
    float length(void)
    {
        return sqrtf(x * x + y * y + z * z);
    }
};