#include "Vec2.hpp"

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