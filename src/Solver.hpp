#pragma once
#include "Classes.hpp"
#include <iostream>
#include <cmath>
constexpr int WIDTH = 1200;
constexpr int HEIGHT = 900;
constexpr int substeps = 100;
constexpr float gravity = 0;
constexpr float BOUNCE_DAMPING = -1;

class Solver{
    SDL_Window *window = nullptr;
    SDL_Surface *surface = nullptr;
    bool is_running = false;
    Circle c1,c2;
    // Spring s1;
    SDL_Event e;
    public:
    Solver(): c1({5,0},{0.0, gravity},{300,500},30,20), c2({2,-3},{0,0},{500,156},20,10) {};
    bool init();
    void collision(Circle &circle,Circle &c2);
    void run();
    ~Solver();
};