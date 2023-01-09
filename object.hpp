#pragma once

#include "engine/body.hpp"
#include "graphics/shape.hpp"
#include "vec.hpp"

class Object
{
public:
    Body *body;
    Shape *shape;

    template<typename T>
    Object(T body, Shape shape)
    {
        this->body = new T(body);
        this->shape = new Shape(shape);
    }
    /**
     * @brief Update graphical shape with physical body data
    **/
    void update()
    {
        shape->setPosition(body->pos);
    }
};