#pragma once
#include "Parser.hpp"
#include <cmath>
constexpr int WIDTH = 1200;
constexpr int HEIGHT = 900;
constexpr int substeps = 100;
constexpr float gravity = 0;
constexpr float BOUNCE_DAMPING = -1;

class Solver{
    SDL_Window *window = nullptr;
    SDL_Surface *surface = nullptr;
    std::vector<SceneObject*> objects;
    Parser parser;
    SDL_Event e;
    bool is_running = false;
    public:
    Solver() = default;
    bool init();
    void out_bounds(Circle &c1);
    void collision(Circle &circle,Circle &c2);
    void run();
    ~Solver();
};