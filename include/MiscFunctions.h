#ifndef MISCFUNCTIONS_H_INCLUDED
#define MISCFUNCTIONS_H_INCLUDED

#include <typeinfo>

template<class C>
inline int getHash(){return typeid(C).hash_code();}

template<class C>
inline int getHash(C c){return typeid(c).hash_code();}

#endif // MISCFUNCTIONS_H_INCLUDED
