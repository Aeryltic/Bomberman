#ifndef TYPEDEFS_H_INCLUDED
#define TYPEDEFS_H_INCLUDED

#include "Structures.h"
class Entity;
class Component;

typedef shared_ptr<Entity>  entity_ptr;
typedef shared_ptr<Component>  component_ptr;

typedef deque<int_vector2d> Path;

#endif // TYPEDEFS_H_INCLUDED
