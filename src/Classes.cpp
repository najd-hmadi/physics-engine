#include "Classes.hpp"

void Entity::step(){
    Vec2 k1x,k2x,k3x,k4x,k1v,k2v,k3v,k4v;
    k1x = m_velocity;
    k1v = m_acceleration;
    k2x = m_velocity + k1x * 0.5 * dt;
    k2v = m_acceleration + k1v * 0.5 * dt;
    k3x = m_velocity + k2x * 0.5 * dt;
    k3v = m_acceleration + k2v * 0.5 * dt;
    k4x = m_velocity + k3x * 0.5 * dt;
    k4v = m_acceleration + k3v * 0.5 * dt;

    m_position = m_position + (k1x + k2x * 2 + k3x * 2 + k4x )* dt * 0.166;
    m_velocity = m_velocity + (k1v + k2v * 2 + k3v * 2 + k4v )* dt * 0.166;
}




Circle::Circle(const Vec2 &vc,const Vec2 &ac,const Vec2 &pos ,double radius,int mass){
        this->m_acceleration = ac;
        this->m_velocity = vc;
        this->m_position = pos;
        this->m_radius = radius;
        this->m_mass = mass;
    }
void Circle::draw_circle(SDL_Surface *surface,Uint32 color){
            int x2 = 0;
            int y2 = m_radius;
            int d = 1 - m_radius;

            while (x2 <= y2) {
                // Draw horizontal lines between the left and right edges for each scanline
                for (int i = m_position.x - x2; i <= m_position.x + x2; i++) {
                    SDL_Rect rect = {i, static_cast<int>(m_position.y + y2), 1, 1};
                    SDL_FillRect(surface, &rect, color);
                    rect.y = m_position.y - y2;
                    SDL_FillRect(surface, &rect, color);
                }
                for (int i = m_position.x - y2; i <= m_position.x + y2; i++) {
                    SDL_Rect rect = {i, static_cast<int>(m_position.y + x2), 1, 1};
                    SDL_FillRect(surface, &rect, color);
                    rect.y = m_position.y - x2;
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

Spring::Spring(Vec2 &&anch, const Vec2 &ball,double rest, double radius){
        this->m_rest_length = rest;
        this->m_anchor = anch;
        this->m_attached_pos = ball;
        this->m_radius = radius;
        this->m_x = sqrt((m_attached_pos.x - m_anchor.x) * (m_attached_pos.x - m_anchor.x) + (m_attached_pos.y - m_anchor.y) * (m_attached_pos.y - m_anchor.y)) - m_rest_length;
}
void Spring::update(Circle c){
        this->m_attached_pos = c.m_position;
        this->m_x = sqrt((m_attached_pos.x - m_anchor.x) * (m_attached_pos.x - m_anchor.x) + (m_attached_pos.y - m_anchor.y) * (m_attached_pos.y - m_anchor.y)) - m_rest_length;
    }
void Spring::draw_circle(SDL_Surface *surface,Uint32 color){
            int x2 = 0;
            int y2 = m_radius;
            int d = 1 - m_radius;

            while (x2 <= y2) {
                // Draw horizontal lines between the left and right edges for each scanline
                for (int i = m_anchor.x - x2; i <= m_anchor.x + x2; i++) {
                    SDL_Rect rect = {i, static_cast<int>(m_anchor.y + y2), 1, 1};
                    SDL_FillRect(surface, &rect, color);
                    rect.y = m_anchor.y - y2;
                    SDL_FillRect(surface, &rect, color);
                }
                for (int i = m_anchor.x - y2; i <= m_anchor.x + y2; i++) {
                    SDL_Rect rect = {i, static_cast<int>(m_anchor.y + x2), 1, 1};
                    SDL_FillRect(surface, &rect, color);
                    rect.y = m_anchor.y - x2;
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
    