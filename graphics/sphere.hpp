#pragma once

#include "GL/gl.h"
#include "shape.hpp"
#include "../common.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

namespace Graphics
{
    /**
     * @brief A sphere shape class 
    **/
    class Sphere
    : public Shape
    {
    public:
        #define SPHERE_SECTOR_COUNT 20
        #define SPHERE_STACK_COUNT 20

        #define SPHERE_DEFAULT_COLOR (Vec3(0.8f, 0.8f, 0.8f)) //default sphere color (light grey)

        /**
         * @brief Create sphere
         * @param radius Sphere radius 
        **/
        Sphere(float radius)
        {
            generate(radius, SPHERE_DEFAULT_COLOR);
        }

        /**
         * @brief Create sphere
         * @param radius Sphere radius
         * @param color Sphere color
        **/
        Sphere(float radius, Vec3 color)
        {
            generate(radius, color);
        }

    private:
        /**
         * @brief Generate sphere
         * @param radius Sphere radius
         * @param color Sphere color
        **/
        void generate(float radius, Vec3 color)
        {   
            //rewritten from http://www.songho.ca/opengl/gl_sphere.html
            
            //use spherical coordinates to calculate vertices and normals
            //stacks are like meridians, sector are like circles of latitude
            //first, calculate points on the sphere
            const float dTheta = 2 * M_PI / SPHERE_SECTOR_COUNT; //delta theta (longitude)
            const float dPhi = M_PI / SPHERE_STACK_COUNT; //delta phi (latitude)
            float theta, phi; //theta (longitude), phi (latitude)
            float x, y, z; //current point on sphere 
            float xy; //radius*cos(phi) - common factor for x and y
            int k1, k2; //temporary triangle vertices indices

            for(int i = 0; i <= SPHERE_STACK_COUNT; i++)
            {
                phi = M_PI / 2 - i * dPhi; //go from pi/2 to -pi/2 (all circles of latitude)
                xy = radius * cosf(phi); //calculate common factor for x and y
                z = radius * sinf(phi);  //calculate z

                k1 = i * (SPHERE_SECTOR_COUNT + 1);     //beginning of the first stack (top left corner)
                k2 = k1 + SPHERE_SECTOR_COUNT + 1;      //end of this stack/beginning of the next stack (bottom left corner)

                for(int j = 0; j <= SPHERE_SECTOR_COUNT; j++, k1++, k2++)
                {
                    theta = j * dTheta; 

                    x = xy * cosf(theta); //calculate points
                    y = xy * sinf(theta); 
                    vertices.push_back(x); //store them
                    vertices.push_back(y);
                    vertices.push_back(z);

                    normals.push_back(x / radius); //calculate normal vector
                    normals.push_back(y / radius);
                    normals.push_back(z / radius);

                    color.pushTo(colors);

                    if((i < SPHERE_STACK_COUNT) && (j < SPHERE_SECTOR_COUNT))
                    {
                        //there are 2 triangles per sector excluding first and last stack (at poles)
                        //make triangles from existing points
                        
                        //triangle at the left side
                        if(i != 0)
                        {
                            indices.push_back(k1);
                            indices.push_back(k2);
                            indices.push_back(k1 + 1);
                        }

                        //triangle at the right side
                        if(i != (SPHERE_STACK_COUNT - 1))
                        {
                            indices.push_back(k1 + 1);
                            indices.push_back(k2);
                            indices.push_back(k2 + 1);
                        }
                    }
                }
            }
        }
    };

};