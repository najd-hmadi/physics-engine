#pragma once
#include "Vec2.hpp"
#include <SDL2/SDL.h>
constexpr double dt = 0.0001;
class Entity{
    public:
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration ;
    int m_mass;
    Vec2 m_p; // momentum
    // takes new acceleration calculated in runtime
    void step();
};
class Circle : public Entity {
    public:
    float radius;
    Circle(Vec2 &&vc,Vec2 &&ac,Vec2 &&pos ,float radius,int mass);
    
    void draw_circle(SDL_Surface *surface,Uint32 color);
};

class Spring {

    public:
    Vec2 anchor;
    Vec2 attached_pos;
    float k = 0.45;
    float rest_length;
    float x;
    int radius;
    void draw_circle(SDL_Surface *surface,Uint32 color);
    Spring(Vec2 &&anch, const Vec2 &ball,float rest, float radius);
    void update(Circle c);
};