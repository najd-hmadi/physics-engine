#include "Vec2.hpp"
Vec2::Vec2(){
    this->x = 0;
    this->y = 0;
}
Vec2::Vec2(const double &x1, const double &y1){
    this->x = x1;
    this->y = y1;
}
Vec2::Vec2(const Vec2 &other){
    this->x = other.x;
    this->y = other.y; 
}
double Vec2::hyp(){
    return sqrt((x*x) + y*y);
}
void Vec2::normalize(){
    float l = sqrt(x * x + y * y);    
        if(l != 0){
            x = x / l;
            y = y / l;
        }
        
}
Vec2 Vec2::operator+( const Vec2 &other) const {
        return { x + other.x, y + other.y };
}
Vec2 Vec2::operator*( const double &scalar ) const{
       return { x * scalar, y * scalar };
}
Vec2 Vec2::operator-( const Vec2 &other) const {
    return { x - other.x, y - other.y };
}