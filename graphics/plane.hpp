#pragma once

#include "GL/gl.h"
#include "shape.hpp"
#include "../common.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

namespace Graphics
{
    #define PLANE_DEFAULT_COLOR (Vec3(1.f, 1.f, 1.f)) //white
    
    /**
     * @brief A plane shape class 
    **/
    class Plane
    : public Shape
    {
    public:
        /**
         * @brief Create plane
         * @param v1 Vertex 1
         * @param v2 Vertex 2
         * @param v3 Vertex 3
         * @param v4 Vertex 4 
        **/
        Plane(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4)
        {
            generate(v1, v2, v3, v4, PLANE_DEFAULT_COLOR);
        }

        /**
         * @brief Create plane
         * @param v1 Vertex 1
         * @param v2 Vertex 2
         * @param v3 Vertex 3
         * @param v4 Vertex 4 
         * @param color Plane color
        **/
        Plane(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4, Vec3 color)
        {
            generate(v1, v2, v3, v4, color);
        }
    private:

        /**
         * @brief Generate plane
         * @param v1 Vertex 1
         * @param v2 Vertex 2
         * @param v3 Vertex 3
         * @param v4 Vertex 4 
         * @param color Plane color
        **/
        void generate(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4, Vec3 color)
        {   
            v1.pushTo(vertices); //store vertices
            v2.pushTo(vertices);
            v3.pushTo(vertices);
            v4.pushTo(vertices);

            Vec3 vn;
            vn = (v2 - v1) * (v4 - v1); //calculate normal vector to the plane
            vn = vn / vn.length(); //make it unity length

            vn.pushTo(normals); //normal vector is same for every vertex
            vn.pushTo(normals);
            vn.pushTo(normals);
            vn.pushTo(normals);
            
            indices.push_back(0); //plane is constructed using two triangles
            indices.push_back(1); //v1-v2-v4 and v2-v3-v4
            indices.push_back(3);
            indices.push_back(1);
            indices.push_back(2);
            indices.push_back(3);

            color.pushTo(colors); //store colors (same for every vertex)
            color.pushTo(colors);
            color.pushTo(colors);
            color.pushTo(colors);
        }
    };

};