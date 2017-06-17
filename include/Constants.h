#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

//#include <SDL.h>
//#include <memory>

//#include <deque>

using namespace std;

//static const int NUM_KEYS = SDL_NUM_SCANCODES;

const int TICKS_PER_SECOND = 20;
const int TIMESTEP = 1000/TICKS_PER_SECOND;

const unsigned GRID_SIZE = 32;
const double MAN_SPEED_MULTIPLIER = 2;
const double MAN_SPEED = MAN_SPEED_MULTIPLIER * GRID_SIZE; // gridy na sekunde

const unsigned INITIAL_BOMB_RANGE = 2;

#endif // CONSTANTS_H_INCLUDED
