#pragma once

#include "../vec.hpp"
#include "collision.hpp"

namespace Bodies
{
    /**
     * @brief Body types 
    **/
    enum Type
    {
        BODY_POINT_PARTICLE,
        BODY_PLANE,
        BODY_NONE,
    };
    
    /**
     * @brief A base class for all physical body types
     * 
     * Can be used on its own to represent a zero-mass, rigid and fixed abstract body (a dummy body for a graphical object with no physical representation).
     * Still can have its collision boundaries.
    **/
    class Body
    {
    public:
        Vec3 pos{}; //center of mass coordinates in meters
        Vec3 v{}; //center of mass velocity in m/s
        float m{}; //mass in kg
        Collision::Boundary *boundary = nullptr; //body boundaries for collision detection

        /**
         * @brief Initialize abstract body object
         * @param pos Initial position
         * @param v Initial velocity
         * @param m Mass in kg
        **/
        Body(Vec3 pos = {0.f, 0.f, 0.f}, Vec3 v = {0.f, 0.f, 0.f}, float m = 0.f)
        : m(m)
        {
            this->pos = pos;
            this->v = v;
        }


        /**
         * @brief Move body according to current velocity
        **/
        virtual void move(void){};

        /**
         * @brief Handle collision with ground plane (x = 0) 
        **/
        virtual void collideWithGround(void){};

        /**
         * @brief Apply forces to body (gravity, drag etc.)
        **/
        virtual void applyForces(void){};

        /**
         * @brief Handle collision with other body
         * @param b The other body to collide with
         * @warning This function changes velocities of both bodies, so must be called only once for the same pair of bodies 
        **/
        virtual void collide(Body *b){};

        /**
         * @brief Get body type
         * @return Body type from enum Bodies::Type 
        **/
        enum Type getBodyType()
        {
            return type;
        }

        /**
         * @brief Check if boundaries are initialized
         * @return True if so, false if not 
        **/
        bool areBoundariesDefined()
        {
            if(boundary == nullptr)
                return false;
            
            return true;
        }
        
    protected:
        enum Type type = BODY_NONE; //body type
    };
};