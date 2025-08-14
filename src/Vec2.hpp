#pragma once
#include <cmath>
struct Vec2{
    double x,y;
    Vec2();
    Vec2(const double &x, const double &y);
    Vec2(const Vec2 &other);
    double hyp();
    void normalize();
    Vec2 operator+( const Vec2 &other) const;
    Vec2 operator*( const double &scalar ) const ;
    Vec2 operator-( const Vec2 &other) const;
};