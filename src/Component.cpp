#include "Component.h"
#include "Entity.h"
#include <cmath>
#include "EntityManager.h"
#include "ObjectFactory.h"
#include "EventManager.h"
#include "MiscFunctions.h"

/// PhysicalForm ---------------------------------------------------------------------------
void PhysicalForm::work(int ms)
{
    /*
    if(!_static)
    {
        if(_v >= 0.00001)
        {
            double  mx = cos(_angle) * _v / 1000.0 * ms,
                    my = sin(_angle) * _v / 1000.0 * ms;
            moveBy(mx,my);
            //printPos();
        }
       // else printf("not moving\n");
    }
   // else printf("static\n");
   */
}
SDL_Rect PhysicalForm::rect(int ms)
{
    SDL_Rect rect = {.x = (int)_x, .y = (int)_y, .w = (int)_w, .h = (int)_h};
//    rect.x += cos(_angle) * _v * ms / 1000.0;
//    rect.y += sin(_angle) * _v * ms / 1000.0;
    return rect;
}

