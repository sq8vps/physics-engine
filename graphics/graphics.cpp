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
    glClearColor(0.2f, 0.2f, 0.2f, 1.f); //set background color to gray
    glClearDepth(1.f); //reset depth
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); //set depth comparison condition
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    GLfloat ambLight[] = {0.2f, 0.2f, 0.2f, 1.f}; //ambient light
    GLfloat diffLight[] = {0.6f, 0.6f, 0.6f, 1.f}; //diffuse light (more intensive)
    GLfloat specLight[] = {1.f, 1.f, 1.f, 1.f};  //specular light (intensive point of light)
    GLfloat lightPos[] = {1.f, 1.f, 1.f};  //light source position

    GLfloat specRefl[] = {1.f, 1.f, 1.f, 1.f}; //material reflectance for specular light


    glLightfv(GL_LIGHT0, GL_AMBIENT, ambLight); //set light source
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);

    glMaterialfv(GL_FRONT, GL_SPECULAR, specRefl); //set material reflectance parameters
    glMaterialf(GL_FRONT, GL_SHININESS, 128);

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
    glPushMatrix();
    
    for(int i = 0; i < wrapperPtr->objects.size(); i++)
        wrapperPtr->objects.at(i).draw();
    
    glPopMatrix();

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