#pragma once

#include "../vec.hpp"

/**
 * @brief A base class for all physical body types
 * 
 * Can be used on its own to represent a zero-size zero-mass abstract body
**/
class Body
{
public:
    Vec3 pos{0.f, 0.f, 0.f}; //center of mass coordinates in meters

    Vec3 v{0.f, 0.f, 0.f}; //center of mass velocity in m/s

    float m; //mass in kg

    /**
     * @brief Initialize abstract body object
     * @param pos Initial position
     * @param m Mass in kg
    **/
    Body(Vec3 pos = {0.f, 0.f, 0.f}, float m = 0.f)
    : m(m)
    {
        this->pos.x = pos.x;
        this->pos.y = pos.y;
        this->pos.z = pos.z;
        v.x = 0.f;
        v.y = 0.f;
        v.z = 0.f;
    }

    /**
     * @brief Move body according to current speed
    **/
    virtual void move(void){};


    virtual void collideWithGround(void){};

    /**
     * @brief Apply forces to body (gravity, drag etc.)
    **/
    virtual void applyForces(void){};
    
private:
    

};