#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <SDL.h>
#include <memory>
#include "Structures.h"
#include <deque>

using namespace std;

static const int NUM_KEYS = SDL_NUM_SCANCODES;

const int TICKS_PER_SECOND = 20;
const int TIMESTEP = 1000/TICKS_PER_SECOND;

class Entity;
class Component;

typedef shared_ptr<Entity>  entity_ptr;
typedef shared_ptr<Component>  component_ptr;

typedef deque<vector2d> Path;

const unsigned GRID_SIZE = 32;
const double MAN_SPEED_MULTIPLIER = 3;
const double MAN_SPEED = MAN_SPEED_MULTIPLIER * GRID_SIZE; // 3 gridi na sekunde

//const int NUMEVENTS = 1;

/*
typedef make_shared<Entity> new_entity;
typedef make_shared<Component> new_entity;
*/
#endif // CONSTANTS_H_INCLUDED
