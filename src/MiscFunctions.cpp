#include "MiscFunctions.h"
#include "Constants.h"



int_vector2d gridFromReal(vector2d real) {return int_vector2d(round(real.x/GRID_SIZE),round(real.y/GRID_SIZE));}
vector2d realFromGrid(int_vector2d grid) {return vector2d(grid.x*GRID_SIZE,grid.y*GRID_SIZE);}

int_vector2d gridFromReal(double rx, double ry) {return int_vector2d(round(rx/GRID_SIZE),round(ry/GRID_SIZE));}
vector2d realFromGrid(int gx, int gy) {return vector2d(gx*GRID_SIZE,gy*GRID_SIZE);}
