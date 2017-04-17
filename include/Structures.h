#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED
#include <cmath>
#include <SDL.h>
#include <memory>
using namespace std;
class Entity;
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
extern int _AliveCount;
struct Vector2D_double
{
    Vector2D_double() : x(0), y(0) {}
    Vector2D_double(double x, double y) : x(x), y(y) {}
    double x,y;
    const double operator-(const Vector2D_double &b) const
    {
        return sqrt((x-b.x)*(x-b.x)+(y-b.y)*(y-b.y));
    }
    const bool operator==(const Vector2D_double &b) const
    {
        return ((abs(x-b.x) < 0.0001) && (abs(y-b.y) < 0.0001));
    }
    const bool operator!=(const Vector2D_double &b) const
    {
        return !((*this)==b);
    }
};

struct Vector2D_int
{
    Vector2D_int() : x(0), y(0) {}
    Vector2D_int(int x, int y) : x(x), y(y) {}
    int x,y;
    const double operator-(const Vector2D_int &b) const
    {
        return sqrt((x-b.x)*(x-b.x)+(y-b.y)*(y-b.y));
    }
    const bool operator==(const Vector2D_int &b) const
    {
        return ((x==b.x) && (y==b.y));
    }
    const bool operator!=(const Vector2D_int &b) const
    {
        return !((*this)==b);
    }
};

typedef Vector2D_double vector2d;
typedef Vector2D_int int_vector2d;
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

struct EntityEvent
{
    Uint32 type;
    Uint32 timestamp;
    shared_ptr<Entity> publisher;
    shared_ptr<Entity> subscriber;
};

#endif // STRUCTURES_H_INCLUDED
