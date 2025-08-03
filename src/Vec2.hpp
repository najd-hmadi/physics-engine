#pragma once
#include <cmath>
struct Vec2{
    double x,y;
    void normalize();
    Vec2 operator+( const Vec2 &other) const;
    Vec2 operator*( const double &scalar ) const ;
    Vec2 operator-( const Vec2 &other) const;
};