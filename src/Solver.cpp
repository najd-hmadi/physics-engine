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
void Solver::collision(Circle &circle){
        if((circle.m_position.y + circle.m_radius > HEIGHT ) || ( circle.m_position.y - circle.m_radius < 0 ) ) circle.m_velocity.y *= BOUNCE_DAMPING ;
        if((circle.m_position.x + circle.m_radius > WIDTH ) || ( circle.m_position.x - circle.m_radius < 0 ) ) circle.m_velocity.x *= BOUNCE_DAMPING ;

    }
void Solver::run(){
        while(is_running){
            while(SDL_PollEvent(&e) != 0){
                if(e.type == SDL_QUIT){
                    is_running = false;
                }
            }
            
            
            // make a unit vector pointing from the anchor of the spring to the circle
            // Vec2 v = s1.attached_pos - s1.anchor;
            // v.normalize();
            // calculate the acceleration caused by the spring and add it to the circle's acceleration (i do not know why but when the circle has another acceleration vector the simulation goes nuts, probably because of euler integration)
            
            c1.draw_circle(surface,0x000000);

            for(int i = 0; i < substeps; i++){
                // calculating the sum of all the acceleration vectors on the circle c1
                c1.m_acceleration =  (Vec2){0.0, gravity} ;
                c1.step();
                collision(c1);
                // s1.update(c1);
            }          
            // s1.draw_circle(surface,0xffffff);
            c1.draw_circle(surface,0xffffff);
            SDL_UpdateWindowSurface(window);
            
            
            // SDL_Delay(1000);
        }
    }
Solver::~Solver(){
        SDL_DestroyWindow(window);
        SDL_Quit();
    }