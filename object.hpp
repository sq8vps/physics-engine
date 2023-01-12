#pragma once

#include "engine/body.hpp"
#include "graphics/shape.hpp"
#include "vec.hpp"


class Object
{
public:
    Bodies::Body *body;
    Graphics::Shape *shape;
    

    template<typename T>
    Object(T body, Graphics::Shape shape)
    {
        this->body = new T(body);
        this->shape = new Graphics::Shape(shape);
        id = getNextID(); //get next ID
    }
    /**
     * @brief Update graphical shape with physical body data
    **/
    void update()
    {
        shape->setPosition(body->pos);
    }

    /**
     * @brief Get object ID
     * @return Object ID 
    **/
    unsigned int getID()
    {
        return id;
    }

private:
    /**
     * @brief Get next free ID for object
     * @return Free object ID
    **/
    static unsigned int getNextID()
    {
        static unsigned int id = 0;
        return id++;
    }

protected:
    unsigned int id; //object id
};