#include <iostream>

#include "engine/pointpart.hpp"
#include "engine/env.hpp"
extern struct Environment env;

int main(int argc, char **argv)
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
    



    
    return 0;
}