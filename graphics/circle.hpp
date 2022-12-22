#pragma once

#include "shapes.hpp"

class Circle
: public Shape
{
private:
    float radius;
    
public:
    void draw();

};