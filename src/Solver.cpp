#include "Solver.hpp"

bool Solver::init(){
        if(SDL_Init(SDL_INIT_VIDEO) < 0) return false;
        window = SDL_CreateWindow("physics engine",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
        if(!window){
            std::cerr <<"no window created";
            return false;
        }
        surface = SDL_GetWindowSurface(window);
        if(!surface){
            std::cerr << "no surface created";
            return false;
        }
        is_running = true;
        return true;
    }
void Solver::collision(Circle &circle,Circle &c2){
        if((circle.m_position.y + circle.m_radius > HEIGHT ) || ( circle.m_position.y - circle.m_radius < 0 ) ) circle.m_velocity.y *= BOUNCE_DAMPING ;
        if((circle.m_position.x + circle.m_radius > WIDTH ) || ( circle.m_position.x - circle.m_radius < 0 ) ) circle.m_velocity.x *= BOUNCE_DAMPING ;
        if((c2.m_position.y + c2.m_radius > HEIGHT ) || ( c2.m_position.y - c2.m_radius < 0 ) ) c2.m_velocity.y *= BOUNCE_DAMPING ;
        if((c2.m_position.x + c2.m_radius > WIDTH ) || ( c2.m_position.x - c2.m_radius < 0 ) ) c2.m_velocity.x *= BOUNCE_DAMPING ;
        if(sqrt((circle.m_position.x - c2.m_position.x) * (circle.m_position.x - c2.m_position.x) + (circle.m_position.y - c2.m_position.y) * (circle.m_position.y - c2.m_position.y)) < circle.m_radius + c2.m_radius ){
            Vec2 temp(c2.m_velocity);
            c2.m_velocity = (circle.m_velocity * 2 * circle.m_mass + c2.m_velocity * (c2.m_mass - circle.m_mass) ) * (1 / (circle.m_mass + c2.m_mass));
            circle.m_velocity = temp - circle.m_velocity + c2.m_velocity;
            std::cout << (1.0 / 2.0 * circle.m_mass * ( circle.m_velocity.hyp() * circle.m_velocity.hyp()) +  1.0 / 2.0 * c2.m_mass * ( c2.m_velocity.hyp() * c2.m_velocity.hyp())) << '\n' ;
        }

    }
void Solver::run(){
        while(is_running){
            while(SDL_PollEvent(&e) != 0){
                if(e.type == SDL_QUIT){
                    is_running = false;
                }
            }
            
            
            
            c1.draw_circle(surface,0x000000);
            c2.draw_circle(surface,0x000000);
            for(int i = 0; i < substeps; i++){
                c1.step();
                c2.step();
                collision(c1,c2);
            }          
            c2.draw_circle(surface,0xffffff);
            c1.draw_circle(surface,0xffffff);
            SDL_UpdateWindowSurface(window);
            
            
            // SDL_Delay(1000);
        }
    }
Solver::~Solver(){
        SDL_DestroyWindow(window);
        SDL_Quit();
    }