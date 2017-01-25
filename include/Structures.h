#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

struct StatusFlags /* jest wcisniety przycisk*/
{
    bool _escape = 0,
        _left = 0,
        _right = 0,
        _up = 0,
        _down = 0;
};

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
#endif // STRUCTURES_H_INCLUDED
