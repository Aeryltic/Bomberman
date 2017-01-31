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

template <class T = double>
struct Vector2D
{
    Vector2D() : x(0), y(0) {}
    Vector2D(T x, T y) : x(x), y(y) {}
    T x,y;
    const T operator-(const Vector2D &b) const
    {
        return sqrt((x-b.x)*(x-b.x)+(y-b.y)*(y-b.y));
    }
    const bool operator==(const Vector2D &b) const
    {
        return ((abs(x*1.0-b.x*1.0)<0.001) && (abs(y*1.0-b.y*1.0)<0.001));
    }
    const bool operator!=(const Vector2D &b) const
    {
        return !((*this)==b);
    }
};

typedef Vector2D<> vector2d;
typedef Vector2D<int> int_vector2d;
struct PositionAndSpeed // obsolete
{
    PositionAndSpeed(){}
    vector2d pos,v;
    void updatePosition(int ms_passed)
    {
        pos.x += v.x * ms_passed / 1000.0;
        pos.y += v.y * ms_passed / 1000.0;
    }
    vector2d interpolated(int ms_passed) const /// "interpolated"
    {
        return vector2d(pos.x + v.x * ms_passed / 1000.0, pos.y + v.y * ms_passed / 1000.0);
    }
};

struct Circle
{
    Circle(double x, double y, double r) : x(x), y(y), r(r) {}
    double x, y, r;
};

#endif // STRUCTURES_H_INCLUDED
