#include <iostream>

#include "engine/pointpart.hpp"
#include "engine/env.hpp"
#include "error.hpp"
#include "graphics/graphics.hpp"
#include <thread>
#include "vec.hpp"
#include "graphics/sphere.hpp"
#include "graphics/plane.hpp"

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
    gui.setCamera(Vec3(2, 1, 2), Vec3(0, 0, 0.f), Vec3(0, 1, 0));
    Sphere sp(0.1f, Vec3(0, 1, 0));
    Plane pl(Vec3(-1, 0, 1), Vec3(1, 0, 1), Vec3(1, 0, -1), Vec3(-1, 0, -1));

    sp.setPosition(0.0f, 0.1f, 0.f);

    gui.add(pl);
    gui.add(sp);

    
    std::thread th(ph);


    gui.exec();
    
    while(1)
    {
        
    }


    
    return EXIT_OK;
}

