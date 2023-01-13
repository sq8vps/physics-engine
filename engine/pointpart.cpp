#include "pointpart.hpp"

#include <cmath>
#include "env.hpp"
#include "../common.hpp"

void Bodies::PointParticle::move(void)
{
    this->pos.x += (this->v.x * env.dt);
    this->pos.y += (this->v.y * env.dt);
    this->pos.z += (this->v.z * env.dt);
}

void Bodies::PointParticle::collideWithGround(void)
{
    //assume ground COR to be 1 (perfectly elastic)
    //only take body COR into consideration

    if((this->pos.y - this->radius) < DISTANCE_DELTA_ZERO)
    {
        this->pos.y = this->radius + DISTANCE_DELTA_ZERO; //add distance delta, otherwise the codition above will be always true
        this->v.y *= -(this->cor); //recalculate velocity after collision
    }
}

void Bodies::PointParticle::applyForces(void)
{
    this->v.y -= (env.g * env.dt); //apply gravitational force
    this->v.y += (env.rho * env.g * volume / m * env.dt); //apply buoyancy force

    float k = 0.5f * env.rho * DRAG_COEFFICIENT * frontalAera; //calculate drag common term
    //apply drag
    //use signum function to apply drag force in the opposite direction to velocity vector
    this->v.x -= (sgn(this->v.x) * this->v.x * this->v.x * k * env.dt);
    this->v.y -= (sgn(this->v.y) * this->v.y * this->v.y * k * env.dt);
    this->v.z -= (sgn(this->v.z) * this->v.z * this->v.z * k * env.dt); 
}


Error_t Bodies::PointParticle::setCOR(float cor)
{
    if((cor < 0.f) || (cor > 1.f))
        return ERR_BAD_COR;

    this->cor = cor;
    
    return OK;
}

void Bodies::PointParticle::collide(Body *b)
 {
    if((this->boundary == nullptr) || (b->boundary == nullptr)) //either object has no boundaries defined?
        return;
    
    if(this->boundary->detect((*b).boundary) == false) //no collision detected?
        return;

    switch(b->getBodyType())
    {
        case Bodies::BODY_POINT_PARTICLE:
            collideWithPointParticle(dynamic_cast<PointParticle*>(b));
            break;
        default:
            break;
    }

}

void Bodies::PointParticle::collideWithPointParticle(PointParticle *b)
{
    Vec3 normal = (b->pos - this->pos) / (b->pos - this->pos).length(); //calculate contact vector (pointing from this object to other object)
    float meff = 1.f / (1.f / this->m + 1.f / b->m); //calculate recuded (efficient) mass
    float vimp = normal.dot(this->v - b->v); //calculate impact speed
    float imp = (1.f + this->cor * b->cor) * meff * vimp; //calculate impulse magnitude

    //calculate and set new velocities
    this->v = this->v - (normal * (imp / this->m));
    b->v = b->v + (normal * (imp / this->m));

    //adjust position slightly so that the detection collision won't detect it
    //again before position are updated
    this->pos = this->pos + (this->v * env.dt * 2);
    b->pos = b->pos + (b->v * env.dt * 2);
}