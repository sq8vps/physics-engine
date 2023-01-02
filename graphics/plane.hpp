#pragma once

#include "GL/gl.h"
#include "shape.hpp"
#include "../common.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

#define PLANE_DEFAULT_COLOR (Vec3(1.f, 1.f, 1.f))

class Plane
: public Shape
{
public:
    Plane(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4)
    {
        generate(v1, v2, v3, v4, PLANE_DEFAULT_COLOR);
    }
    Plane(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4, Vec3 color)
    {
        generate(v1, v2, v3, v4, color);
    }
private:

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
