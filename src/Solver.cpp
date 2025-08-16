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
        objects = parser.parse();
        return true;
    }
void Solver::out_bounds(Circle &circle){
    if((circle.m_position.y + circle.m_radius > HEIGHT ) || ( circle.m_position.y - circle.m_radius < 0 ) ) circle.m_velocity.y *= BOUNCE_DAMPING ;
    if((circle.m_position.x + circle.m_radius > WIDTH ) || ( circle.m_position.x - circle.m_radius < 0 ) ) circle.m_velocity.x *= BOUNCE_DAMPING ;
}
void Solver::collision(Circle &circle,Circle &c2){
        
        if(sqrt((circle.m_position.x - c2.m_position.x) * (circle.m_position.x - c2.m_position.x) + (circle.m_position.y - c2.m_position.y) * (circle.m_position.y - c2.m_position.y)) < circle.m_radius + c2.m_radius ){
            Vec2 temp(c2.m_velocity);
            c2.m_velocity = (circle.m_velocity * 2 * circle.m_mass + c2.m_velocity * (c2.m_mass - circle.m_mass) ) * (1 / (circle.m_mass + c2.m_mass));
            circle.m_velocity = temp - circle.m_velocity + c2.m_velocity;
        }

    }
// this run function is so terrible it runs at least at least at O(n^3 * substeps) for every frame this is atrocious
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
            
            for(auto object : objects){
                
                object->render(surface,0x000000);
                
            }
            for(auto object : objects){
                Spring *ptr = dynamic_cast<Spring*>(object);
                if(ptr) ptr->update();
            }
            for(int i = 0; i < substeps; i++){
                
                for(auto object : objects){
                    Circle *ptr2 = dynamic_cast<Circle*>(object);
                    if(ptr2){
                        ptr2->step();
                    }
                    
                }
                
            }
            
            for(int i = 0; i< objects.size();i++){
                    Circle * ptr = dynamic_cast<Circle*>(objects[i]);
                        for(int j = i+1; j < objects.size(); j++){
                            Circle *ptr2 = dynamic_cast<Circle*>(objects[j]);
                            if(ptr && ptr2) collision(*ptr,*ptr2);
                        }
                    if(ptr) out_bounds(*ptr);
                }      
            for(auto object : objects){
                object->render(surface,0xffffff);
            }
            SDL_UpdateWindowSurface(window);
            
            
            // SDL_Delay(1000);
        }
    }
Solver::~Solver(){
        for(auto object : objects){
            delete object;
        }
        SDL_DestroyWindow(window);
        SDL_Quit();
    }