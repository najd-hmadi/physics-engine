#pragma once
#include "Vec2.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include "SceneObject.hpp"
constexpr double dt = 0.001;


class Entity{
    public:
    Vec2 force;
    Vec2 m_position;
    Vec2 m_velocity;
    Vec2 m_acceleration ;
    double m_mass;
    Vec2 m_p; // momentum
    // takes new acceleration calculated in runtime
    void step();
    void add_force(const Vec2 &other);
};
class Circle : public Entity, public SceneObject {
    public:
    double m_radius;
    Circle() = default;
    Circle(const Vec2 &pos ,const Vec2 &vc,const Vec2 &ac,double radius,int mass);
    
    void render(SDL_Surface *surface,Uint32 color) const override;
};

class Spring : public SceneObject {

    public:
    Circle *m_attached_circle;
    Vec2 m_anchor;
    Vec2 m_last_v;
    double m_k = 0.25;
    double m_rest_length;
    double m_x;
    int m_radius;
    void render(SDL_Surface *surface,Uint32 color) const override;
    Spring() = default;
    Spring(Vec2 &&anch,Circle *c ,double rest, double radius);
    void update();
};