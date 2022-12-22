#pragma once

/**
 * Environment settings
*/

#define DEFAULT_TIME_STEP 0.001f //1 ms
#define DEFAULT_ENV_RHO 1.240f //standard density of air
#define DEFAULT_ENV_MU 0.0000181f //standard dynamic viscosity of air
#define DEFAULT_GRAVITY 9.8f //standard gravity on Earth

#define DISTANCE_DELTA_ZERO 0.001f //maximum distance difference between to objects to be treated as zero

struct Environment
{
    float dt{DEFAULT_TIME_STEP}; //time step in s
    float rho{DEFAULT_ENV_RHO}; //environment density in kg/m^3
    float mu{DEFAULT_ENV_RHO}; //dynamic viscosity in Pa*s
    float g{DEFAULT_GRAVITY}; //standard gravity in m/s^2

    float t{0.f}; //current time value in s
};

extern struct Environment env;
