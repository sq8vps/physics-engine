#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "object.hpp"

using namespace std;

class Terminal
{
public:

    void start();

    void bindObjects(std::vector<Object> *objects)
    {
        this->objects = objects;
    }
private:
    void addObject();

    std::vector<Object> *objects;
};