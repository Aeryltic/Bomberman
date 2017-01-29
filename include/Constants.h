#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <SDL.h>
#include <memory>

using namespace std;

static const int NUM_KEYS = SDL_NUM_SCANCODES;

const int TICKS_PER_SECOND = 20;
const int TIMESTEP = 1000/TICKS_PER_SECOND;

class Entity;
class Component;

typedef shared_ptr<Entity>  entity_ptr;
typedef shared_ptr<Component>  component_ptr;
/*
typedef make_shared<Entity> new_entity;
typedef make_shared<Component> new_entity;
*/
#endif // CONSTANTS_H_INCLUDED
