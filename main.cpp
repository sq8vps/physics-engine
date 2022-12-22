#include <iostream>

#include "engine/pointpart.hpp"
#include "engine/env.hpp"
#include "error.hpp"
#include "graphics/graphics.hpp"
#include <thread>
#include "vec.hpp"


void ph()
{
    PointParticle p(5.f, 10.f, 1.f);
    p.setCOR(0.5f);
    float t = 2;
    for(int i = 0; i < (t / env.dt); i++)
    {
        p.applyForces();
        p.collideWithGround();
        p.move();
        std::cout << "x: " << p.pos.x << " y: " << p.pos.y << " vy: " << p.v.y << std::endl;
    }
}

int main(int argc, char **argv)
{
    Graphics gui(640, 480, 45);
    gui.setCamera(Vec3(0, 0, 0), Vec3(0,0,-100), Vec3(0, -1, 0));
    
    std::thread th(ph);


    gui.exec();
    
    while(1)
    {
        
    }


    
    return EXIT_OK;
}

