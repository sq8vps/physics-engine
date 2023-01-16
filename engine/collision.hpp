#pragma once

#include "../vec.hpp"
#include "body.hpp"
#include <vector>

namespace Collision
{
    class Spheres;
    class Box;
    
    //boundary types
    enum Type
    {
        BOUNDARY_SPHERE,
        BOUNDARY_BOX,
        BOUNDARY_NONE,
    };

    /**
     * @brief A class for collision boundaries and detection
    **/
    class Boundary
    {
    public:
        /**
         * @brief Initialize collision boundary object
        **/
        Boundary()
        {
        }

        /**
         * @brief Update local body position
         * @param pos New position
         * @attention Must be updated by the program on every position change 
        **/
        void updateBodyPos(Vec3 &pos)
        {
            bodyPos = pos;
        }

        /**
         * @brief Detect collision between two objects
         * @param *other Other object boundary pointer
         * @return True if collision detected, false if no collision detected
        */
        virtual bool detect(Boundary *other)
        {
            return false;
        }

        /**
         * @brief Add bounding sphere
         * @param pos Sphere position relative to object center
         * @param radius Sphere radius
         * @attention Has no effect on Collision::Box boundary model object 
        **/
        virtual void addSphere(Vec3 pos, float radius){};
        
        /**
         * @brief Get boundary type
         * @return Boundary type from enum Collision::Type
        */
        enum Type getBoundaryType()
        {
            return type;
        }



    protected:
        Vec3 bodyPos{}; //current body position
        enum Type type = BOUNDARY_NONE; //boundary type

    };



    /**
     * @brief A class for collision boundaries made of at least one sphere
    **/
    class Spheres
    : public Boundary
    {
    public:    
        struct Sphere //an internal sphere structure
        {
            Vec3 pos; //position relative to object center
            float radius; //sphere radius
        };
        std::vector<Sphere> spheres; //vector of spheres making the full boundary

        /**
         * @brief Initialize sphere collision boundary object
        **/
        Spheres()
        : Collision::Boundary()
        {
            type = BOUNDARY_SPHERE;
        }

        /**
         * @brief Detect collision between two objects
         * @param *other Other object boundary pointer
         * @return True if collision detected, false if no collision detected
        */
        bool detect(Boundary *other)
        {
            switch(other->getBoundaryType())
            {
                case BOUNDARY_SPHERE:
                    return detect(*(dynamic_cast<Spheres*>(other)));
                    break;
                case BOUNDARY_BOX:
                    //return detect(*(dynamic_cast<Box*>(other)));
                    break;
                default:
                    return false;
                    break;
            }
            return false;
        }

        /**
         * @brief Detect collision between sphere-bounded bodies
         * @param *other Other body boundary object (spheres)
         * @return True if collision detected, false if no collision detected
        */
        bool detect(Spheres &other)
        {
            //check if any spheres overlap
            for(Spheres::Sphere s1 : spheres)
            {
                for(Spheres::Sphere s2 : other.spheres)
                {
                    //calculate distance between centers of spheres and compare with sum of radii
                    //also shift spheres according to body position
                    if(((s1.pos + bodyPos) - (s2.pos + other.bodyPos)).length() <= (s1.radius + s2.radius))
                        return true;
                }
            }
            return false; //no spheres overlap - no collision
        }

        /**
         * @brief Detect collision between sphere-bounded and box-bounded bodies
         * @param *other Other body boundary object (box)
         * @return True if collision detected, false if no collision detected
        */
        bool detect(Box &other)
        {
            return false;
        }

        /**
         * @brief Add bounding sphere
         * @param pos Sphere position relative to object center
         * @param radius Sphere radius 
        **/
        void addSphere(Vec3 pos, float radius)
        {
            spheres.push_back(Sphere{pos, radius});
        }

        
    };


    /**
     * @brief A cuboid collision boundary box class 
     * @warning Not implemented yet!
    **/
    class Box
    : public Boundary
    {
    public:
        std::vector<Vec3> vertices; //3 boundary box vertices

        /**
         * @brief Detect collision between sphere-bounded and box-bounded bodies
         * @param *other Other body boundary object (spheres)
         * @return True if collision detected, false if no collision detected
        */
        bool detect(Spheres &other)
        {
            return false;
        }

        /**
         * @brief Detect collision between box-bounded bodies
         * @param *other Other body boundary object (box)
         * @return True if collision detected, false if no collision detected
        */
        bool detect(Box &other)
        {
            return false;
        }
    };
};