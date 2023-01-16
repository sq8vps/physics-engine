#pragma once

#include <GL/gl.h>
#include "../vec.hpp"
#include "shape.hpp"
#include "../object.hpp"

namespace Graphics
{
    #define GRAPHICS_DEFAULT_DIM_X 800 //default screen dimensions
    #define GRAPHICS_DEFAULT_DIM_Y 600
    #define GRAPHICS_DEFAULT_FOV 45. //default field of view

    #define GRAPHICS_DEFAULT_CAM_PHI 0.f //deault camera phi = 0
    #define GRAPHICS_DEFAULT_CAM_THETA 1.1780972451f //default camera theta = 3pi/8
    #define GRAPHICS_DEFAULT_CAM_RADIUS 10.f //defalt camera radius

    #define GRAPHICS_MAX_CAM_RADIUS 50.f //max camera radius
    #define GRAPHICS_MIN_CAM_RADIUS 0.2f //minimum camera radius

    #define GRAPHICS_CAM_ANGLE_STEP 0.08726646259f //camera phi and theta step = 5 degrees
    #define GRAPHICS_CAM_RADIUS_STEP 0.1f //camera radius step

    /**
     * @brief General graphic engine, rendering and timing class 
    **/
    class Graphics
    {
    public:
        /**
         * @brief Initialize graphics module
         * @param dimX X screen dimension in pixels
         * @param dimY Y screen dimension in pixels
         * @param fov Field of view in degrees
        **/
        Graphics(int dimX = GRAPHICS_DEFAULT_DIM_X, int dimY = GRAPHICS_DEFAULT_DIM_Y, double fov = GRAPHICS_DEFAULT_FOV);

        ~Graphics();

        /**
         * @brief Start execution of graphics engine and simulation in general
         * @attention Enters infinite loop 
        **/
        void exec();

        /**
         * @brief Set camera by specyfing vectors
         * @param eye Eye position
         * @param at Point to look at
         * @param up Camera orientation vector 
        **/
        void setCamera(Vec3 eye, Vec3 at, Vec3 up);

        /**
         * @brief Set camera by specifying angles (spherical coordinates)
         * @param phi Phi in rad
         * @param theta Theta in rad
         * @param radius Radius 
        **/
        void setCameraSpherical(float phi, float theta, float radius);

        /**
         * @brief Set default camera position
        **/
        void setCameraDefaults();

        /**
         * @brief Bind vector of objects to be rendered
         * @param *obj Object vector 
        **/
        void bindObjects(std::vector<Object> *obj);

        /**
         * @brief Set simulation timer callback
         * @param *cb Callback function
         * 
         * Set function to be called on every tick. Timer frequency is equal to SIMULATION_RATE. 
        **/
        void setSimulationTimerCallback(void (*cb)());

        /**
         * @brief Start simulation, that is enable timer callback
        **/
        void start();

        /**
         * @brief Stop simulation, that is disable timer callback
         * @attention Does not stop rendering, so that the camera can be manipulated 
        **/
        void stop();

    private:
        int dimX{}; //window width in pixels
        int dimY{}; //window height in pixels
        double fov{}; //field of view in Y axis in degrees
        double ratio{}; //current width-to-height viewport ratio
        Vec3 camEye{0.f, 0.f, 2.f}, camAt{0.f, 0.f, 0.f}, camUp{0.f, 1.f, 0.f}; //view transform (camera) vectors
        float camPhi = GRAPHICS_DEFAULT_CAM_PHI, camTheta = GRAPHICS_DEFAULT_CAM_THETA, camRadius = GRAPHICS_DEFAULT_CAM_RADIUS; //camera spherical coordinates
        bool started = 0; //is simulation started (ongoing?)

        //these function need to be static in order to pass its pointer to OpenGL libraries (which are written in C)
        //these function should be called ONLY by OpenGL
        /**
         * @brief Update window, render objects etc. 
        **/
        static void updateWindow();

        /**
         * @brief Reshape window
         * @param x New X dimension
         * @param y New Y dimension 
        **/
        static void reshapeWindow(GLsizei x, GLsizei y);

        /**
         * @brief Handle keyboard input
         * @param key Pressed key
         * @param x Cursor x position on screen
         * @param y Cursor y position on screen 
        **/
        static void keyboardInput(unsigned char key, int x, int y);

        /**
         * @brief Handle special keyboard input
         * @param key Pressed key code
         * @param x Cursor x position on screen
         * @param y Cursor y position on screen 
        **/
        static void specialKeyboardInput(int key, int x, int y);

        /**
         * @brief Handle OpenGL timer tick
         * @param val Timer index
        **/
        static void timerInternal(int val);

        std::vector<Object> *objects; //pointer to object storage vector

        void (*simulationTimerCb)() = nullptr; //simulation timer callback function pointer
    };

};