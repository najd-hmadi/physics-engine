#include "Classes.hpp"

void Entity::step(){
    Vec2 k1x,k2x,k3x,k4x,k1v,k2v,k3v,k4v;
    k1x = velocity;
    k1v = acceleration;
    k2x = velocity + k1x * 0.5 * dt;
    k2v = acceleration + k1v * 0.5 * dt;
    k3x = velocity + k2x * 0.5 * dt;
    k3v = acceleration + k2v * 0.5 * dt;
    k4x = velocity + k3x * 0.5 * dt;
    k4v = acceleration + k3v * 0.5 * dt;

    position = position + (k1x + k2x * 2 + k3x * 2 + k4x )* dt * 0.166;
    velocity = velocity + (k1v + k2v * 2 + k3v * 2 + k4v )* dt * 0.166;
}




Circle::Circle(Vec2 &&vc,Vec2 &&ac,Vec2 &&pos ,float radius,int mass){
        this->acceleration = ac;
        this->velocity = vc;
        this->position = pos;
        this->radius = radius;
        this->m_mass = mass;
    }
void Circle::draw_circle(SDL_Surface *surface,Uint32 color){
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

Spring::Spring(Vec2 &&anch, const Vec2 &ball,float rest, float radius){
        this->rest_length = rest;
        this->anchor = anch;
        this->attached_pos = ball;
        this->radius = radius;
        this->x = sqrt((attached_pos.x - anchor.x) * (attached_pos.x - anchor.x) + (attached_pos.y - anchor.y) * (attached_pos.y - anchor.y)) - rest_length;
}
void Spring::update(Circle c){
        this->attached_pos = c.position;
        this->x = sqrt((attached_pos.x - anchor.x) * (attached_pos.x - anchor.x) + (attached_pos.y - anchor.y) * (attached_pos.y - anchor.y)) - rest_length;
    }
void Spring::draw_circle(SDL_Surface *surface,Uint32 color){
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