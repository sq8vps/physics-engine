#pragma once

#include "body.hpp"
#include "../error.hpp"

class PointParticle
: public Body
{
private:
    float cor{1.f}; //coefficient of restitution (unitless)
    float radius{1.f}; //a point particle doesn't have any radius, but for graphic representation we need a non-zero one

public:


    PointParticle(Vec3 pos, float m, float radius, float cor = 1.f)
    : Body(pos, m), radius(radius), cor(cor)
    {

    }
    Error_t setCOR(float cor);

    void move(void);
    void collideWithGround(void);
    void applyForces(void);

};
