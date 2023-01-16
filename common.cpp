#include "common.hpp"
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include "engine/env.hpp"
#include "graphics/graphics.hpp"
#include "error.hpp"

struct Config config{false, false, GRAPHICS_DEFAULT_DIM_X, GRAPHICS_DEFAULT_DIM_Y, DEFAULT_RANDOM_OBJECT_COUNT};

float randf(float min, float max)
{ 
    return min + static_cast <float>(std::rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

float sgn(float val) 
{
    if(val < 0.f)
        return -1.f;
    else if(val > 0.f)
        return 1.f;
    
    return 0.f;
}

using std::cout;
using std::endl;

void parseOptions(int argc, char **argv)
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
                cout << endl << "Usage: physics-engine [-k scale] [-n count] [-x dim] [-y dim] [-g] [-a]" << endl;
                cout << "Options:" << endl;
                cout << "-k scale   Set time scaling. Defaults to " << DEFAULT_TIME_SCALING << "." << endl;
                cout << "-n count   Specify number of randomly generated objects. Defaults to " << DEFAULT_RANDOM_OBJECT_COUNT << "." << endl;
                cout << "-x dim     Set window X dimension. Defaults to " << GRAPHICS_DEFAULT_DIM_X << "." << endl;
                cout << "-y dim     Set window Y dimension. Defaults to " << GRAPHICS_DEFAULT_DIM_Y << "." << endl;
                cout << "-g         Disable GUI. Prints physics engine output to console. GUI is enabled by default." << endl;
                cout << "-a         Do not autostart simulation. Autostart is enabled by default." << endl;
                exit(EXIT_OK);
                break;
            case 'x': //set x dimension
                config.dimX = atoi(optarg);
                break;
            case 'y': //set y dimension
                config.dimY = atoi(optarg);
                break;
            case ':': //there was an argument that required an operand but it was not supplied
                cout << "Option -" << (char)optopt << " requires an operand" << endl;
                exit(EXIT_ARG);
                break;
            case '?': //unrecognised option
                cout << "Option -" << (char)optopt << " was not recognised. Use -h to print help page." << endl;
                exit(EXIT_ARG);
                break;
            default:
                cout << "Unexpected value encountered while parsing arguments" << endl;
                exit(EXIT_ARG);
                break;
        }
    }
}