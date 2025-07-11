#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#define WIDTH 1200
#define HEIGHT 900
const double dt = 0.0001;
const int substeps = 1000;

struct Vec2{
    double x,y;
    void normalize(){
        float l = sqrt(x * x + y * y);
        std::cout << l << "****";
        // if(l = 0) return ;
        x = x / l;
        y = y / l;
    }
    Vec2 operator+( const Vec2 &other) const {
        return { x + other.x, y + other.y };
    }
    Vec2 operator*( const double &scalar ) const{
        return { x * scalar, y * scalar };
    }
    Vec2 operator-( const Vec2 &other) const {
        return { x - other.x, y - other.y };
    }
};

class Entity{
    public:
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration ;
    int m_mass;
    Vec2 m_p; // momentum
    void step(){
        position = position + velocity * dt ;
        velocity = velocity + acceleration * dt;
        // m_p = velocity * m_mass; for later to implement elastic collisions
    }
};

class Circle : public Entity {
    public:
    float radius;
    Circle(Vec2 &&ac,Vec2 &&pos ,float radius,int mass){
        this->acceleration = ac;
        this->position = pos;
        this->radius = radius;
        this->m_mass = mass;
    }
    
    void draw_circle(SDL_Surface *surface,Uint32 color){
            int x2 = 0;
            int y2 = radius;
            int d = 1 - radius;

            while (x2 <= y2) {
                // Draw horizontal lines between the left and right edges for each scanline
                for (int i = position.x - x2; i <= position.x + x2; i++) {
                    SDL_Rect rect = {i, static_cast<int>(position.y + y2), 1, 1};
                    SDL_FillRect(surface, &rect, color);
                    rect.y = position.y - y2;
                    SDL_FillRect(surface, &rect, color);
                }
                for (int i = position.x - y2; i <= position.x + y2; i++) {
                    SDL_Rect rect = {i, static_cast<int>(position.y + x2), 1, 1};
                    SDL_FillRect(surface, &rect, color);
                    rect.y = position.y - x2;
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
// class ForceGenerator{
//     double ax,ay;
//     public:
//     void accelerate(Entity &object, double  ){
        
//     }
// };
class Spring : public Entity {

    public:
    float k = 0.45;
    Vec2 anchor;
    float rest_length;
    float x;
    int radius;
    void draw_circle(SDL_Surface *surface,Uint32 color){
            int x2 = 0;
            int y2 = radius;
            int d = 1 - radius;

            while (x2 <= y2) {
                // Draw horizontal lines between the left and right edges for each scanline
                for (int i = anchor.x - x2; i <= anchor.x + x2; i++) {
                    SDL_Rect rect = {i, static_cast<int>(anchor.y + y2), 1, 1};
                    SDL_FillRect(surface, &rect, color);
                    rect.y = anchor.y - y2;
                    SDL_FillRect(surface, &rect, color);
                }
                for (int i = anchor.x - y2; i <= anchor.x + y2; i++) {
                    SDL_Rect rect = {i, static_cast<int>(anchor.y + x2), 1, 1};
                    SDL_FillRect(surface, &rect, color);
                    rect.y = anchor.y - x2;
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
    Spring() {
        this->velocity = {0, 0};
        this->acceleration = {0, 0};
        this->m_mass = 0;

    }
    Spring(Vec2 &&anch, const Vec2 &ball,float rest, float radius){
        this->velocity = {0, 0};
        this->acceleration = {0, 0};
        this->m_mass = 0;


        this->rest_length = rest;
        this->anchor = anch;
        this->position = ball;
        this->radius = radius;
        this->x = sqrt((position.x - anchor.x) * (position.x - anchor.x) + (position.y - anchor.y) * (position.y - anchor.y)) - rest_length;
    }
    void update(Circle c){
        this->position = c.position;
        this->x = sqrt((position.x - anchor.x) * (position.x - anchor.x) + (position.y - anchor.y) * (position.y - anchor.y)) - rest_length;
    }
};
class Solver{
    SDL_Window *window = nullptr;
    SDL_Surface *surface = nullptr;
    bool is_running = false;
    Circle c1;
    Spring s1;
    SDL_Event e;
    public:
    Solver(): c1({0.0, 0.98f},{300,500},30,20) {};
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
        s1 = Spring({300,10},c1.position,200,10);
        return true;
    }
    void out_bounds(Circle &circle){
        if((circle.position.y + circle.radius > HEIGHT ) || ( circle.position.y - circle.radius < 0 ) ) circle.velocity.y *= -0.6 ;
            if((circle.position.x + circle.radius > WIDTH ) || ( circle.position.x - circle.radius < 0 ) ) circle.velocity.x *= -0.6 ;

    }
    void run(){
        while(is_running){
            while(SDL_PollEvent(&e) != 0){
                if(e.type == SDL_QUIT){
                    is_running = false;
                }
            }

            
            c1.draw_circle(surface,0x000000);
            s1.draw_circle(surface,0x000000);
            for(int i = 0; i < substeps; i++){
                c1.step();
                out_bounds(c1);
            }          
            c1.draw_circle(surface,0xffffff);
            SDL_UpdateWindowSurface(window);
            
            s1.update(c1);
            Vec2 v = s1.position - s1.anchor;
            v.normalize();
            c1.acceleration = c1.acceleration + ( v * -s1.k ) ;
            std::cout << c1.acceleration.y << "////" << ( v * -s1.k ).x << "//////" << ( v * -s1.k ).y << '\n';
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