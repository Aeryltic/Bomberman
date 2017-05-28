#include "MiscFunctions.h"

vec3d random_point_in_range(double x, double y, double r_min, double r_max)
{
    double angle = (rand()%360) * M_PI / 180.0;
    double dist = rand()%int(r_max-r_min) + r_min;
    double px = dist * cos(angle) + x,
           py = dist * sin(angle) + y;
    return vec3d(px, py, 0);
}
