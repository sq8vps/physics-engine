#pragma once

#include <GL/gl.h>
#include "../common.hpp"

class Shape
{
public:
    virtual void draw() = 0;
    void move(float x, float y, float z)
    {
        glTranslatef(x, y, z);
    }
    void rotate(float angle, float x, float y, float z)
    {
        glRotatef(RAD2DEG(angle), x, y, z);
    }
};

