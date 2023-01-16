#include <iostream>
#include <unistd.h>
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
#include <cstdlib>
#include "terminal.hpp"



std::vector<Object> objects; //all objects (physical object + graphical shapes) table

using std::cout;
using std::endl;

/**
 * @brief Do simulation. Process physics, refresh shapes.
**/
void doSimulation()
{
    for(unsigned int t = 0; t < (env.k / (SIMULATION_RATE * env.dt)); t++) //process physics with specified time scaling (env.k)
    {
        unsigned int startingObject = 1; //starting object index for collision detection
        for(Object o : objects)  //apply to all objects
        {
            o.body->applyForces(); //apply environmental forces
            o.body->collideWithGround(); //collide with ground - a simplification for this moment
            for(unsigned int i = startingObject; i < objects.size(); i++) //collide every pair of objects, but with no repetition!
            {
                if(!o.body->areBoundariesDefined() || !objects[i].body->areBoundariesDefined()) //check if both bodies have collision boundaries defined
                    continue;
                o.body->collide(objects[i].body); //collide bodies
                o.body->boundary->updateBodyPos(o.body->pos); //update positions
                objects[i].body->boundary->updateBodyPos(objects[i].body->pos);
            }
            startingObject++; //set new starting object index to avoid pair repetition
            o.body->move(); //move object according to its velocity
            if(config.noGui) //gui disabled? print to stdout
            {
                if(o.body->getBodyType() != Bodies::BODY_NONE) //print only for non-dummy objects
                    cout << "Object [" << o.getID() << "] at " << o.body->pos << " velocity " << o.body->v << endl;
            }
        }
    }

    for(Object o : objects) //update graphical shapes
        o.update();
}

/**
 * @brief Add random object to object buffer 
**/
void addRandomParticle()
{
    Vec3 pos(randf(-2.f, 2.f), randf(0.1f, 3.f), randf(-2.f, 0.2f));
    Vec3 v((randf(-1.f, 1.f), randf(-1.f, 1.f), randf(-1.f, 1.f)));
    Vec3 color(randf(0.f, 1.f), randf(0.f, 1.f), randf(0.f, 1.f));
    float radius = randf(0.01f, 0.3f);
    float m = randf(0.01f, 5.f);
    float cor = randf(0.1f, 1.f);
    objects.push_back(Object(Bodies::PointParticle(pos, m, radius, v, cor), Graphics::Sphere(radius, color))); //a sphere treated as a point particle
    objects.back().update(); //update shape position
}

int main(int argc, char **argv)
{
    parseOptions(argc, argv); //parse command line options

    std::srand(std::time(nullptr)); //initialize random number generator

    Terminal term; //initialize terminal
    term.bindObjects(&objects); //pass object vector pointer to terminal
    std::thread termThread(&Terminal::start, &term); //start terminal in separate thread

    objects.push_back(Object(Bodies::Body(), Graphics::Plane(Vec3(-10, 0, 10), Vec3(10, 0, 10), Vec3(10, 0, -10), Vec3(-10, 0, -10)))); //add a plane with dummy body

    for(; config.nRandom > 0; config.nRandom--) //generate random particles
        addRandomParticle();

    if(config.noGui == false) //gui enabled?
    {
        Graphics::Graphics gui(config.dimX, config.dimY, 45); //create GUI with 640x480 window, 45 degress FOV
        gui.bindObjects(&objects); //bind object storage to GUI

        gui.setSimulationTimerCallback(&doSimulation); //set simulation callback to process physics and set new object positions
        
        if(config.noAutostart == false) //autostart enabled
            gui.start(); //start simulation

        gui.exec(); //start GUI execution. Enters the loop - must be the last function called
    }
    else //gui disabled?
    {
        while(1)
        {
            doSimulation(); //just simulate
        }
    }
    return EXIT_OK;
}

