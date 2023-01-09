#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

#define SIMULATION_RATE 30.f //simulation rate in Hz

#define DEG2RAD(deg) (static_cast<double>(deg) * M_PI / 180.)
#define RAD2DEG(rad) (rad / M_PI * 180.)