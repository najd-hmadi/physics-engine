#include <iostream>
#include <SDL2/SDL.h>
#define WIDTH 1200
#define HEIGHT 900
const double dt = 0.00001;
const int substeps = 10000;
class Entity{
    public:
    double x,y;
    double vx =0,vy =0;
    double ax = 0 ,ay;
    double mass;
    void step(){
        x += vx * dt ;
        y += vy * dt ;
        vx += ax * dt ;
        vy += ay * dt;
    }
};
class Circle : public Entity {
    public:
    float radius;
    Circle(double ay,double x,double y,float radius){
        this->ay = ay;
        this->x = x;
        this->y = y;
        this->radius = radius;
    }
    
    void draw_circle(SDL_Surface *surface,Uint32 color){
            int x2 = 0;
            int y2 = radius;
            int d = 1 - radius;

            while (x2 <= y2) {
                // Draw horizontal lines between the left and right edges for each scanline
                for (int i = x - x2; i <= x + x2; i++) {
                    SDL_Rect rect = {i, static_cast<int>(y + y2), 1, 1};
                    SDL_FillRect(surface, &rect, color);
                    rect.y = y - y2;
                    SDL_FillRect(surface, &rect, color);
                }
                for (int i = x - y2; i <= x + y2; i++) {
                    SDL_Rect rect = {i, static_cast<int>(y + x2), 1, 1};
                    SDL_FillRect(surface, &rect, color);
                    rect.y = y - x2;
                    SDL_FillRect(surface, &rect, color);
                }
                if (d < 0) {
                    d += 2 * x2 + 3;
                } else {
                    d += 2 * (x2 - y2) + 5;
                    y2--;
                }
                x2++;
            }
        }
};
class Solver{
    SDL_Window *window = nullptr;
    SDL_Surface *surface = nullptr;
    bool is_running = false;
    Circle c1;
    SDL_Event e;
    public:
    Solver(): c1(0.98f,300,500,30){};
    bool init(){
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
    void out_bounds(Circle &circle){
        if((circle.y + circle.radius > HEIGHT ) || ( circle.y - circle.radius < 0 ) ) circle.vy *= -0.6 ;
        if((circle.x + circle.radius > WIDTH ) || ( circle.x - circle.radius < 0 ) ) circle.vx *= -0.6 ;

    }
    void run(){
        while(is_running){
            while(SDL_PollEvent(&e) != 0){
                if(e.type == SDL_QUIT){
                    is_running = false;
                }
            }

            
            c1.draw_circle(surface,0x000000);
            for(int i = 0; i < substeps; i++){
                c1.step();
                out_bounds(c1);
            }          
            c1.draw_circle(surface,0xffffff);
            SDL_UpdateWindowSurface(window);
            // SDL_Delay(10);
            
        }
    }
    ~Solver(){
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

int main(int argc, char* argv[]){
    Solver s1;
    if(s1.init()){
        s1.run();
    }
    else{
        std::cout << "could not initialize solver";
    }
    return 0;
}