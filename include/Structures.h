#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED
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
};
struct PositionAndSpeed
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
#endif // STRUCTURES_H_INCLUDED
