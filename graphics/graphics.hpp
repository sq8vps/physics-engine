#pragma once

#include <GL/gl.h>
#include "../vec.hpp"

#define GRAPHICS_DEFAULT_DIM_X 800
#define GRAPHICS_DEFAULT_DIM_Y 600
#define GRAPHICS_DEFAULT_FOV 45.

class Graphics
{
public:
    Graphics(int dimX = GRAPHICS_DEFAULT_DIM_X, int dimY = GRAPHICS_DEFAULT_DIM_Y, double fov = GRAPHICS_DEFAULT_FOV);
    ~Graphics();
    void exec();
    void setCamera(Vec3 eye, Vec3 at, Vec3 up);
    void setCameraDefaults();


    
private:
    int dimX; //window width in pixels
    int dimY; //window height in pixels
    double fov; //field of view in Y axis in degrees
    double ratio; //current width-to-height viewport ratio
    Vec3 camEye, camAt, camUp; //view transform (camera) vectors
    static void updateWindow();
    static void reshapeWindow(GLsizei x, GLsizei y);
};