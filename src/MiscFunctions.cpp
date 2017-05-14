#include "MiscFunctions.h"
#include "Constants.h"



int_vector2d gridFromReal(vector2d real) {return int_vector2d(round(real.x/GRID_SIZE),round(real.y/GRID_SIZE));}
vector2d realFromGrid(int_vector2d grid) {return vector2d(grid.x*GRID_SIZE,grid.y*GRID_SIZE);}

int_vector2d gridFromReal(double rx, double ry) {return int_vector2d(round(rx/GRID_SIZE),round(ry/GRID_SIZE));}
vector2d realFromGrid(int gx, int gy) {return vector2d(gx*GRID_SIZE,gy*GRID_SIZE);}

vec3d random_point_in_range(double x, double y, double r_min, double r_max)
{
    double angle = (rand()%360) * M_PI / 180.0;
    double dist = rand()%int(r_max-r_min) + r_min;
    double px = dist * cos(angle) + x,
           py = dist * sin(angle) + y;
    return vec3d(px, py, 0);
}
