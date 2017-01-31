#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED
#include <cmath>
/// na przyszlosc
/*
enum VarType
{
    INT32,
    INT64,
    DOUBLE64,
    CHAR,
    STRING
};
union VarUnion
{
    int int32;
    long long int64;
    double double64;
    char character;
};
struct Variable
{
    VarType _type;
    VarUnion _val;
};
*/
///-------------------

struct Vector2D
{
    Vector2D() : x(0), y(0) {}
    Vector2D(double x, double y) : x(x), y(y) {}
    double x,y;
    const double operator-(const Vector2D &b) const
    {
        return sqrt((x-b.x)*(x-b.x)+(y-b.y)*(y-b.y));
    }
    const bool operator==(const Vector2D &b) const
    {
        return ((x==b.x) && (y==b.y));
    }
    const bool operator!=(const Vector2D &b) const
    {
        return !((*this)==b);
    }
};

struct PositionAndSpeed // obsolete
{
    PositionAndSpeed(){}
    Vector2D pos,v;
    void updatePosition(int ms_passed)
    {
        pos.x += v.x * ms_passed / 1000.0;
        pos.y += v.y * ms_passed / 1000.0;
    }
    Vector2D interpolated(int ms_passed) const /// "interpolated"
    {
        return Vector2D(pos.x + v.x * ms_passed / 1000.0, pos.y + v.y * ms_passed / 1000.0);
    }
};

struct Circle
{
    Circle(double x, double y, double r) : x(x), y(y), r(r) {}
    double x, y, r;
};

#endif // STRUCTURES_H_INCLUDED
