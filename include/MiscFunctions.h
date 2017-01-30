#ifndef MISCFUNCTIONS_H_INCLUDED
#define MISCFUNCTIONS_H_INCLUDED

#include <typeinfo>
#include <cmath>

template<class C>
inline int getHash(){return typeid(C).hash_code();}

template<class C>
inline int getHash(C c){return typeid(c).hash_code();}

inline double degrees(double angle){return angle * 180.0 / M_PI;} // angle - kat w radianach

#endif // MISCFUNCTIONS_H_INCLUDED
