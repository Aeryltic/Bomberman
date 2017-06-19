#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <cmath>
//#include <memory>
#include <sstream>

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif // _USE_MATH_DEFINES

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct vec3d {
    double x, y, z;

    vec3d(double x, double y, double z) : x(x), y(y), z(z) {}
    vec3d(): x(0), y(0), z(0) {}

    double dist(const vec3d &other) const {
        return sqrt((x-other.x)*(x-other.x)+(y-other.y)*(y-other.y)+(z-other.z)*(z-other.z));
    }

    double len() const {
        return sqrt(x*x+y*y+z*z);
    }

    vec3d operator+(const vec3d &other) const {
        return vec3d(x + other.x, y + other.y, z + other.z);
    }

    vec3d operator-(const vec3d &other) const {
        return vec3d(x - other.x, y - other.y, z - other.z);
    }

    void operator+=(const vec3d &other) {
        (x += other.x, y += other.y, z += other.z);
    }

    vec3d operator*(const double &v) const {
        return vec3d(x*v, y*v, z*v);
    }

    vec3d operator/(const double &v) const {
        return vec3d(x/v, y/v, z/v);
    }

    vec3d operator-() const {
        return vec3d(-x,-y,-z);
    }

    vec3d moved_towards(const vec3d &other, double step) const {
        double distance = dist(other);
        return step >= distance ? other : (*this) + (other - *this) * step / distance;
    }

    vec3d movement_step(const vec3d &other, double step) const {
        double distance = dist(other);
        return step >= distance ? (other - *this) : (other - *this) * step / distance;
    }

    vec3d normalized() const {
        double l = len();
        return l > 0.00001 ? *this / l : vec3d(0,0,0);
    }

    double angle_to(const vec3d& other) const {
        vec3d n1 = normalized();
        vec3d n2 = other.normalized();
        return acos(n1.x * n2.x + n1.y * n2.y + n1.z * n2.z);
    }

    double dot_product(const vec3d& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    vec3d slided_along(vec3d other) const {
        //printf("sliding %s along %s: ",repr().c_str(), other.repr().c_str());
        //double angle = angle_to(other);
        //if(abs(angle) > M_PI / 2)other = -other;
        //printf("angle = %f", angle * 180.0 / M_PI);
        //if(abs(angle) > M_PI || angle < 0.00001) return *this;
        //double l = dot_product(other) / other.len();
        return other.normalized() * len();
    }

    std::string repr() const {
        std::stringstream fmt;
        fmt << x << " " << y << " " << z;
        return fmt.str();
    }

    vec3d random_in_range(double r_min, double r_max)
    {
        double angle = (rand()%360) * M_PI / 180.0;
        double dist = rand()%int(r_max - r_min) + r_min;
        double px = dist * cos(angle) + x,
               py = dist * sin(angle) + y;
        return vec3d(px, py, 0);
    }
};
/*
struct EntityEvent
{
    unsigned type;
    unsigned timestamp;
    shared_ptr<Entity> publisher;
    shared_ptr<Entity> subscriber;
};
*/

/*
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
*/

/*
struct Circle
{
    Circle(double x, double y, double r) : x(x), y(y), r(r) {}
    double x, y, r;
};
*/
/// na przyszlosc... raczej nie
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
    double float64;
    char chr;
};
struct Variable
{
    VarType _type;
    VarUnion _val;
};
*/
///-------------------
//extern int _AliveCount;
#endif // STRUCTURES_H_INCLUDED
