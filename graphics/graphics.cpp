#include "graphics.hpp"

#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <GL/glu.h>

#include "../error.hpp"
#include "glut.h"


Graphics *wrapperPtr = nullptr;

Graphics::Graphics(int dimX, int dimY, double fov)
{
    wrapperPtr = this;
    
    if(dimX < 1 || dimY < 1)
    {
        this->dimX = GRAPHICS_DEFAULT_DIM_X;
        this->dimY = GRAPHICS_DEFAULT_DIM_Y;
    }

    if((fov <= 0.) || (fov > 90.))
        this->fov = GRAPHICS_DEFAULT_FOV;

    this->dimX = dimX;
    this->dimY = dimY;
    this->fov = fov;
    
    int d1 = 0;
    char *d2[1];
    glutInit(&d1, d2); //init GLUT with empty arguments
    glutInitWindowSize(this->dimX, this->dimY); //set initial window dimensions
    glutInitWindowPosition(-1, -1); //let the window system choose position
    glutInitDisplayMode(GLUT_DOUBLE); //double buffering
    glutCreateWindow("Physics engine GUI"); //create window with specified title
    glutDisplayFunc(this->updateWindow); //register all callbacks
    glutReshapeFunc(Graphics::reshapeWindow);
    glutIdleFunc(Graphics::updateWindow);
    glClearColor(0.f, 0.f, 0.f, 1.f); //set background color to black
    glClearDepth(1.f); //reset depth
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); //set depth comparison condition
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    setCameraDefaults();
}

Graphics::~Graphics()
{

}

void Graphics::updateWindow()
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   //clear buffers
   
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    

    //glEnableClientState(GL_COLOR_ARRAY);
    //glEnableClientState(GL_VERTEX_ARRAY);
    //glColorPointer(3, GL_FLOAT, 0, colors1);
    //glVertexPointer(3, GL_FLOAT, 0, vertices1);
    glPushMatrix();
    
    for(int i = 0; i < wrapperPtr->objects.size(); i++)
        wrapperPtr->objects.at(i).draw();
    
    glPopMatrix();

    //glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
    //glDisableClientState(GL_COLOR_ARRAY);

    glutSwapBuffers();
}

void Graphics::reshapeWindow(GLsizei x, GLsizei y)
{
    glViewport(0, 0, x, y); //set viewport dimensions

    wrapperPtr->dimX = x;
    wrapperPtr->dimY = y;
    wrapperPtr->ratio = static_cast<GLdouble>(wrapperPtr->dimX) / static_cast<GLdouble>(wrapperPtr->dimY); //calculate new aspect ratio

    wrapperPtr->setCamera(wrapperPtr->camEye, wrapperPtr->camAt, wrapperPtr->camUp); //update projection and view transform matrices
}

void Graphics::exec()
{  
    glutMainLoop();
}

void Graphics::setCamera(Vec3 eye, Vec3 at, Vec3 up)
{
    camEye = eye;
    camAt = at;
    camUp = up;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(wrapperPtr->fov, wrapperPtr->ratio, 0.1f, 100.f);
    gluLookAt(camEye.x, camEye.y, camEye.z, camAt.x, camAt.y, camAt.z, camUp.x, camUp.y, camUp.z);
}

void Graphics::setCameraDefaults()
{
    setCamera(Vec3(0.f, 0.f, 0.f), Vec3(0.f, 0.f, -100.f), Vec3(0.f, 1.f, 0.f));
}

void Graphics::add(Shape &object)
{
    objects.push_back(object);
}