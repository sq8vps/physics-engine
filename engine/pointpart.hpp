#pragma once

#include "body.hpp"
#include "../error.hpp"
#include "collision.hpp"

namespace Bodies
{
    /**
     * @brief A point particle body class 
    **/
    class PointParticle
    : public Body
    {
    private:
        #define DRAG_COEFFICIENT 0.47f //sphere drag coefficient

        float cor{}; //coefficient of restitution (unitless)
        float radius{}; //a point particle doesn't have any radius, but for graphic representation we need a non-zero one
        float volume{}; //a volume
        float frontalAera{}; //sphere frontal area

        /**
         * @brief Collide with another point particle
         * @param *b Other point particle pointer 
        **/
        void collideWithPointParticle(PointParticle *b);
    public:

        /**
         * @brief Initialize point particle object
         * @param pos Body position
         * @param m Body mass
         * @param radius Spere radius (needed for graphical representation and collision detection)
         * @param v Initial velocity
         * @param cor Coefficient of restitution 
        **/
        PointParticle(Vec3 pos, float m, float radius, Vec3 v, float cor)
        : Body(pos, v, m), radius(radius), cor(cor)
        {
            boundary = new Collision::Spheres();
            boundary->addSphere(Vec3(), radius); //add bounding sphere at the center
            type = BODY_POINT_PARTICLE;
            boundary->updateBodyPos(this->pos);
            volume = 4.f / 3.f * static_cast<float>(M_PI) * radius * radius * radius; //precalculate volume
            frontalAera = static_cast<float>(M_PI) * radius * radius; //precalculate frontal area
        }

        /**
         * @brief Initialize point particle object
         * @param pos Body position
         * @param m Body mass
         * @param radius Spere radius (needed for graphical representation and collision detection)
         * @param v Initial velocity
        **/
        PointParticle(Vec3 pos, float m, float radius, Vec3 v)
        : Body(pos, v, m), radius(radius), cor(cor)
        {
            PointParticle(pos, m, radius, v, 1.0f);
        }

        /**
         * @brief Initialize point particle object
         * @param pos Body position
         * @param m Body mass
         * @param radius Spere radius (needed for graphical representation and collision detection)
         * @param cor Coefficient of restitution 
        **/
        PointParticle(Vec3 pos, float m, float radius, float cor)
        : Body(pos, Vec3(), m), radius(radius), cor(cor)
        {
            PointParticle(pos, m, radius, Vec3(), cor);
        }

        /**
         * @brief Set coefficient of restitution for body
         * @param cor New COR 
        **/
        Error_t setCOR(float cor);

        /**
         * @brief Move body according to current velocity
        **/
        void move(void);

        /**
         * @brief Handle collision with ground plane (x = 0) 
        **/
        void collideWithGround(void);

        /**
         * @brief Apply forces to body (gravity, drag etc.)
        **/
        void applyForces(void);

        /**
         * @brief Handle collision with other body
         * @param b The other body to collide with
         * @warning This function changes velocities of both bodies, so must be called only once for the same pair of bodies 
        **/
        void collide(Body *b);

    };
};
