#include <iostream>

#include "engine/pointpart.hpp"
#include "engine/env.hpp"
#include "error.hpp"
#include "graphics/graphics.hpp"
#include <thread>
#include "vec.hpp"
#include "graphics/sphere.hpp"
#include "graphics/plane.hpp"
#include <vector>
#include "object.hpp"

std::vector<Object> objects; //all objects (physical object + graphical shapes) table

void doSimulation()
{
    for(unsigned int t = 0; t < (1.f / (SIMULATION_RATE * env.dt)); t++) //process physics in real time
    {
        for(Object o : objects)  //apply to all objects
        {
            o.body->applyForces();
            o.body->collideWithGround();
            o.body->move();
        }
    }

    for(Object o : objects) //update graphical shapes
        o.update();
}

int main(int argc, char **argv)
{
    Graphics gui(640, 480, 45); //create GUI with 640x480 window, 45 degress FOV
    gui.bindObjects(&objects); //bind object storage to GUI
    gui.setCamera(Vec3(2, 1, 2), Vec3(0, 0, 0.f), Vec3(0, 1, 0)); //set camera to (2,1,2) looking at the center

    //create initial objects
    objects.push_back(Object(PointParticle(Vec3(0.f, 0.5f, 0.f), 1.f, 0.1f, 0.8f), Sphere(0.1f, Vec3(0, 1, 0)))); //a sphere treated as a point particle
    objects.push_back(Object(PointParticle(Vec3(0.5f, 0.5f, 0.f), 1.f, 0.15f, 0.9f), Sphere(0.15f, Vec3(1, 0, 0)))); //a sphere treated as a point particle
    objects.push_back(Object(Body(), Plane(Vec3(-1, 0, 1), Vec3(1, 0, 1), Vec3(1, 0, -1), Vec3(-1, 0, -1)))); //a plane with dummy body

    gui.setSimulationTimerCallback(&doSimulation); //set simulation callback to process physics and set new object positions
    gui.start(); //start simulation

    gui.exec(); //start GUI execution. Enters the loop - must be the last function called

    return EXIT_OK;
}

