#ifndef MISCFUNCTIONS_H_INCLUDED
#define MISCFUNCTIONS_H_INCLUDED

#include <typeinfo>
#include <cmath>
#include <SDL.h>
#include <Structures.h>

/// BOSKIE MAKRO
#define tindex(a) type_index(typeid(a))


/*
template<class C>
inline int getHash() {return typeid(C).hash_code();}

template<class C>
inline int getHash(C c) {return typeid(c).hash_code();}
*/
inline double degrees(double angle) {return angle * 180.0 / M_PI;} // angle - kat w radianach

inline bool collide(SDL_Rect *a, SDL_Rect *b) {return SDL_HasIntersection(a,b);}

int_vector2d gridFromReal(vector2d real);
vector2d realFromGrid(int_vector2d grid);

int_vector2d gridFromReal(double rx, double ry);
vector2d realFromGrid(int gx, int gy);

vec3d random_point_in_range(double x, double y, double r_min, double r_max);

#endif // MISCFUNCTIONS_H_INCLUDED
