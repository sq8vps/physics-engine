#include "terminal.hpp"

#include "vec.hpp"
#include "common.hpp"
#include "engine/body.hpp"
#include "graphics/shape.hpp"
#include "graphics/sphere.hpp"
#include "engine/pointpart.hpp"

void Terminal::start()
{
    while(1)
    {
        cout << "cmd: ";
        string s;
        cin >> s; //read command
        if(s == "add") //add object cmd
            addObject();
        else if(s == "help")
        {
            cout << "Available commands: " << endl;
            cout << "add - add object" << endl;
            cout << "help - show help page" << endl;
        }
        else
           cout << "Unknown command" << endl; 
    }
}

void Terminal::addObject()
{
    Vec3 pos;
    Vec3 v;
    Vec3 color;
    float radius;
    float cor = 1.f;
    float m;
    cout << "Position x: ";
    cin >> pos.x;
    cout << "Position y: ";
    cin >> pos.y;
    cout << "Position z: ";
    cin >> pos.z;
    cout << "Radius: ";
    cin >> radius;
    cout << "Mass: ";
    cin >> m;
    cout << "Set initial velocity (y/N)? ";
    string s;
    cin.ignore();
    getline(cin, s);
    if((s == "y") || (s == "Y"))
    {
        cout << "Velocity x: ";
        cin >> v.x;
        cout << "Velocity y: ";
        cin >> v.y;
        cout << "Velocity z: ";
        cin >> v.z;
    }
    cout << "Set coefficient of restitution (y/N)? ";
    cin.ignore();
    getline(cin, s);
    if((s == "y") || (s == "Y"))
    {
        cout << "COR: ";
        cin >> cor;
    }
    cout << "Set color (y/N)? ";
    cin.ignore();
    getline(cin, s);
    if((s == "y") || (s == "Y"))
    {
        cout << "Color R: ";
        cin >> color.x;
        cout << "Color G: ";
        cin >> color.y;
        cout << "Color B: ";
        cin >> color.z;
    }
    else
    {
        color = Vec3(randf(0.f, 1.f), randf(0.f, 1.f), randf(0.f, 1.f));
    }
    objects->push_back(Object(Bodies::PointParticle(pos, m, radius, v, cor), Graphics::Sphere(radius, color)));
    objects->back().update(); //update shape position
    cout << "Object added" << endl;
}