#pragma once

#include "body.hpp"
#include "../error.hpp"
#include "collision.hpp"

namespace Bodies
{
    class PointParticle
    : public Body
    {
    private:
        float cor{1.f}; //coefficient of restitution (unitless)
        float radius{1.f}; //a point particle doesn't have any radius, but for graphic representation we need a non-zero one

    public:


        PointParticle(Vec3 pos, float m, float radius, Vec3 v, float cor)
        : Body(pos, v, m), radius(radius), cor(cor)
        {
            boundary = new Collision::Spheres();
            boundary->addSphere(Vec3(), radius); //add bounding sphere at the center
            type = BODY_POINT_PARTICLE;
            boundary->updateBodyPos(this->pos);
        }
        PointParticle(Vec3 pos, float m, float radius, Vec3 v)
        : Body(pos, v, m), radius(radius), cor(cor)
        {
            PointParticle(pos, m, radius, v, 1.0f);
        }
        PointParticle(Vec3 pos, float m, float radius, float cor)
        : Body(pos, Vec3(), m), radius(radius), cor(cor)
        {
            PointParticle(pos, m, radius, Vec3(), cor);
        }

        Error_t setCOR(float cor);

        void move(void);
        void collideWithGround(void);
        void applyForces(void);
        void collide(Body *b);
    private:
        void collideWithPointParticle(PointParticle *b);

    };
};
