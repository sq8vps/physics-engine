#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "object.hpp"

/**
 * @brief A class for handling user input in terminal 
**/
class Terminal
{
public:

    /**
     * @brief Start terminal
     * @attention Enters infinite loop. Must be executed in separate thread. 
    **/
    void start();

    /**
     * @brief Bind object table
     * @attention Object should be bound before starting terminal 
    **/
    void bindObjects(std::vector<Object> *objects)
    {
        this->objects = objects;
    }
private:

    /**
     * @brief Handle user input for adding new object
    */
    void addObject();

    std::vector<Object> *objects; //pointer to objects table
};