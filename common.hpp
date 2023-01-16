#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

#define SIMULATION_RATE 30.f //simulation rate in Hz
#define DEFAULT_RANDOM_OBJECT_COUNT (10) //default number of random objects to be generated

#define DEG2RAD(deg) (static_cast<double>(deg) * M_PI / 180.) //degrees to radians conversion macro
#define RAD2DEG(rad) (rad / M_PI * 180.) //radians to degrees conversion macro

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
};

extern struct Config config;

/**
 * @brief Get random float from range
 * @param min Lower bound
 * @param max Higher bound
 * @return Random float 
**/
float randf(float min, float max);

/**
 * @brief Get sign of a value
 * @param val Value to check the sign of
 * @return Sign of the value, that is -1, 0 or 1 
**/
float sgn(float val);

/**
 * @brief Parse command line arguments
 * @param argc Argument count
 * @param argv Argument values
*/
void parseOptions(int argc, char **argv);