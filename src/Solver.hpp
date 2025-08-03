#pragma once
#include "Classes.hpp"
#include <iostream>
constexpr int WIDTH = 1200;
constexpr int HEIGHT = 900;
constexpr int substeps = 1000;
constexpr float gravity = 0.98;
constexpr float BOUNCE_DAMPING = -1;

class Solver{
    SDL_Window *window = nullptr;
    SDL_Surface *surface = nullptr;
    bool is_running = false;
    Circle c1;
    // Spring s1;
    SDL_Event e;
    public:
    Solver(): c1({5,0},{0.0, gravity},{300,500},30,20) {};
    bool init();
    void collision(Circle &circle);
    void run();
    ~Solver();
};