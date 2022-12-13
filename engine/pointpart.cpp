#include "pointpart.hpp"

#include <cmath>
#include "env.hpp"
extern struct Environment env;

void PointParticle::move(void)
{
    this->pos.x += (this->v.x * env.dt);
    this->pos.y += (this->v.y * env.dt);
}

void PointParticle::collideWithGround(void)
{
    //assume ground COR to be 1 (perfectly elastic)
    //only take body COR into consideration

    if(this->pos.y < DISTANCE_DELTA_ZERO)
    {
        this->pos.y = 0.f;
        this->v.y *= -(this->cor);
    }
}

void PointParticle::applyForces(void)
{
    this->v.y -= (env.g * env.dt);
}


Error_t PointParticle::setCOR(float cor)
{
    if((cor < 0.f) || (cor > 1.f))
        return ERR_BAD_COR;

    this->cor = cor;
    
    return OK;
}