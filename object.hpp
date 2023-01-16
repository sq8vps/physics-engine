#pragma once

#include "engine/body.hpp"
#include "graphics/shape.hpp"
#include "vec.hpp"

/**
 * @brief A class representing any object: physical body + graphical shape 
**/
class Object
{
public:
    Bodies::Body *body = nullptr; //physical body
    Graphics::Shape *shape = nullptr; //graphical shape

    /**
     * @brief Create object: bind body and shape
     * @param body Body object
     * @param shape Shape object
    **/
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