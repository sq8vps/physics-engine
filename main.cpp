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
#include <unistd.h>
#include <cstdlib>
#include "terminal.hpp"

std::vector<Object> objects; //all objects (physical object + graphical shapes) table

using namespace Bodies;
using namespace Graphics;
using namespace std;

#define DEFAULT_RANDOM_OBJECT_COUNT (10) //default number of random objects to be generated

/**
 * @brief A configuration structure for options chosen with arguments 
**/
struct Config
{
    bool noGui;
    bool noAutostart;
    int dimX;
    int dimY;
    int nRandom;
} config{false, false, GRAPHICS_DEFAULT_DIM_X, GRAPHICS_DEFAULT_DIM_Y, DEFAULT_RANDOM_OBJECT_COUNT};

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
            o.body->move(); //move objects according to their velocities
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

void addRandomParticle()
{
    Vec3 pos(randf(-2.f, 2.f), randf(0.1f, 3.f), randf(-2.f, 0.2f));
    Vec3 v((randf(-1.f, 1.f), randf(-1.f, 1.f), randf(-1.f, 1.f)));
    Vec3 color(randf(0.f, 1.f), randf(0.f, 1.f), randf(0.f, 1.f));
    float radius = randf(0.01f, 0.3f);
    float m = randf(0.01f, 5.f);
    float cor = randf(0.1f, 1.f);
    objects.push_back(Object(PointParticle(pos, m, radius, v, cor), Sphere(radius, color))); //a sphere treated as a point particle
    objects.back().update(); //update shape position
}

int main(int argc, char **argv)
{
    //parse options
    int opt;
    while((opt = getopt(argc, argv, "-:k:n:gahx:y:")) != -1)
    {
        switch(opt)
        {
            case 'k': //time scaling
                env.k = atof(optarg);
                break;
            case 'n': //generate n random objects
                config.nRandom = atoi(optarg);
                break;
            case 'g': //disable gui
                config.noGui = true;
                break;
            case 'a': //no autostart
                config.noAutostart = true;
                break;
            case 'h': //show help
                
                break;
            case 'x': //set x dimension
                config.dimX = atoi(optarg);
                break;
            case 'y': //set y dimension
                config.dimY = atoi(optarg);
                break;
            case ':': //there was an argument that required an operand but it was not supplied
                cout << "Option -" << (char)optopt << " requires an operand" << endl;
                return -1;
                break;
            case '?': //unrecognised option
                cout << "Option -" << (char)optopt << " was not recognised. Use -h to print help page." << endl;
                return -1;
                break;
            default:
                cout << "Unexpected value encountered while parsing arguments" << endl;
                return -1;
                break;
        }
    }

    std::srand(std::time(nullptr)); //initialize random number generator

    Terminal term;
    term.bindObjects(&objects);
    std::thread termThread(&Terminal::start, &term);

    objects.push_back(Object(Body(), Plane(Vec3(-10, 0, 10), Vec3(10, 0, 10), Vec3(10, 0, -10), Vec3(-10, 0, -10)))); //add a plane with dummy body

    for(; config.nRandom > 0; config.nRandom--) //generate random particles
        addRandomParticle();

    if(config.noGui == false)
    {
        Graphics::Graphics gui(config.dimX, config.dimY, 45); //create GUI with 640x480 window, 45 degress FOV
        gui.bindObjects(&objects); //bind object storage to GUI

        gui.setSimulationTimerCallback(&doSimulation); //set simulation callback to process physics and set new object positions
        
        if(config.noAutostart == false) //autostart enabled
            gui.start(); //start simulation

        gui.exec(); //start GUI execution. Enters the loop - must be the last function called
    }
    else
    {
        while(1)
        {
            doSimulation();
        }
    }
    return EXIT_OK;
}

