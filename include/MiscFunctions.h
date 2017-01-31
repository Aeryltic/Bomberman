#ifndef MISCFUNCTIONS_H_INCLUDED
#define MISCFUNCTIONS_H_INCLUDED

#include <typeinfo>
#include <cmath>
#include <SDL.h>

template<class C>
inline int getHash(){return typeid(C).hash_code();}

template<class C>
inline int getHash(C c){return typeid(c).hash_code();}

inline double degrees(double angle){return angle * 180.0 / M_PI;} // angle - kat w radianach

inline bool collide(SDL_Rect *a, SDL_Rect *b){return SDL_HasIntersection(a,b);}
#endif // MISCFUNCTIONS_H_INCLUDED
