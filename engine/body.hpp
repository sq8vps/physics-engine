#pragma once

class Body
{
public:
    struct Pos //center of mass coordinates in meters
    {
        float x;
        float y;
    } pos;

    struct V //center of mass velocity in m/s
    {
        float x;
        float y;
    } v;

    float m; //mass in kg

    Body(float x, float y, float m)
    : m(m)
    {
        pos.x = x;
        pos.y = y;
        v.x = 0.f;
        v.y = 0.f;
    }


    virtual void move(void) = 0;
    virtual void collideWithGround(void) = 0;
    virtual void applyForces(void) = 0;
    
};