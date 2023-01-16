#pragma once

/**
 * Environment settings
*/

#define INTERNAL_TIME_STEP 0.0001f //100 us
#define DEFAULT_ENV_RHO 1.240f //standard density of air
#define DEFAULT_GRAVITY 9.8f //standard gravity on Earth
#define DEFAULT_TIME_SCALING 1.f //no time scaling

#define DISTANCE_DELTA_ZERO 0.001f //maximum distance difference between to objects to be treated as zero

struct Environment
{
    float dt{INTERNAL_TIME_STEP}; //time step in s
    float rho{DEFAULT_ENV_RHO}; //environment density in kg/m^3
    float g{DEFAULT_GRAVITY}; //standard gravity in m/s^2

    float k{DEFAULT_TIME_SCALING}; //time scaling coefficient
};

extern struct Environment env;
