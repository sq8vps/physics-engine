#include "pointpart.hpp"

#include <cmath>
#include "env.hpp"

void PointParticle::move(void)
{
    this->pos.x += (this->v.x * env.dt);
    this->pos.y += (this->v.y * env.dt);
    this->pos.z += (this->v.z * env.dt);
}

void PointParticle::collideWithGround(void)
{
    //assume ground COR to be 1 (perfectly elastic)
    //only take body COR into consideration

    if((this->pos.y - this->radius) < DISTANCE_DELTA_ZERO)
    {
        this->pos.y = this->radius + DISTANCE_DELTA_ZERO; //add distance delta, otherwise the codition above will be always true
        this->v.y *= -(this->cor); //recalculate velocity after collision
    }
}

void PointParticle::applyForces(void)
{
    this->v.y -= (env.g * env.dt); //apply gravitational force
}


Error_t PointParticle::setCOR(float cor)
{
    if((cor < 0.f) || (cor > 1.f))
        return ERR_BAD_COR;

    this->cor = cor;
    
    return OK;
}