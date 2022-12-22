#pragma once

#include "body.hpp"
#include "../error.hpp"

class PointParticle
: public Body
{
private:
    float cor{1.f}; //coefficient of restitution (unitless)

public:


    PointParticle(float x, float y, float m)
    : Body(x, y, m)
    {

    }
    Error_t setCOR(float cor);
    


    void move(void);
    void collideWithGround(void);
    void applyForces(void);

};
