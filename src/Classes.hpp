#pragma once
#include "Vec2.hpp"
#include <SDL2/SDL.h>
constexpr double dt = 0.001;


class Entity{
    public:
    Vec2 m_position;
    Vec2 m_velocity;
    Vec2 m_acceleration ;
    double m_mass;
    Vec2 m_p; // momentum
    // takes new acceleration calculated in runtime
    void step();
};
class Circle : public Entity {
    public:
    double m_radius;
    Circle(const Vec2 &vc,const Vec2 &ac,const Vec2 &pos ,double radius,int mass);
    
    void draw_circle(SDL_Surface *surface,Uint32 color);
};

class Spring {

    public:
    Vec2 m_anchor;
    Vec2 m_attached_pos;
    double m_k = 0.45;
    double m_rest_length;
    double m_x;
    int m_radius;
    void draw_circle(SDL_Surface *surface,Uint32 color);
    Spring(Vec2 &&anch, const Vec2 &ball,double rest, double radius);
    void update(Circle c);
};