#pragma once
#include "Classes.hpp"
#include <iostream>
constexpr int WIDTH = 1200;
constexpr int HEIGHT = 900;
constexpr int substeps = 1000;
constexpr float gravity = 0.98;
constexpr float BOUNCE_DAMPING = -0.6;

class Solver{
    SDL_Window *window = nullptr;
    SDL_Surface *surface = nullptr;
    bool is_running = false;
    Circle c1;
    Spring s1;
    SDL_Event e;
    public:
    Solver(): c1({0.0, gravity},{300,500},30,20),s1({300,10},c1.position,400,10) {};
    bool init();
    void out_bounds(Circle &circle);
    void run();
    ~Solver();
};