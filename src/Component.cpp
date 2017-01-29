#include "Component.h"
#include "InputManager.h"
#include "Entity.h"
#include <cmath>
/*
void PCControllerComponent::setActive()
{
    if((_iManager != nullptr) && (_target->getComponent<MovementComponent>())) /// potrzebuje klawiatury i jego target musi umiec sie poruszac
    {
        _active = true;
    }
}
*/
void PCControllerComponent::setActive()
{
    if(_target->hasComponent<PhysicalFormComponent>() && _iManager != nullptr)
        _active = true;
}
void PCControllerComponent::work(int ms)
{
    if(_iManager->keyStatus(SDLK_w) & (KEY_PRESSED|KEY_DOWN))
    {
        _target->getComponent<PhysicalFormComponent>()->setSpeedToMax();
        _target->getComponent<PhysicalFormComponent>()->setAngle(M_PI/2);
        /// go up
    }
    else if(_iManager->keyStatus(SDLK_s) & (KEY_PRESSED|KEY_DOWN))
    {
        _target->getComponent<PhysicalFormComponent>()->setSpeedToMax();
        _target->getComponent<PhysicalFormComponent>()->setAngle(M_PI*3/2);
        /// go down
    }
    else if(_iManager->keyStatus(SDLK_a) & (KEY_PRESSED|KEY_DOWN))
    {
        _target->getComponent<PhysicalFormComponent>()->setSpeedToMax();
        _target->getComponent<PhysicalFormComponent>()->setAngle(M_PI);
        /// go left
    }
    else if(_iManager->keyStatus(SDLK_d) & (KEY_PRESSED|KEY_DOWN))
    {
        _target->getComponent<PhysicalFormComponent>()->setSpeedToMax();
        _target->getComponent<PhysicalFormComponent>()->setAngle(0);
        /// go right
    }
    else _target->getComponent<PhysicalFormComponent>()->setSpeed(0);
    // bomb dropping
    if(_iManager->keyStatus(SDLK_SPACE) & (KEY_PRESSED))
    {
        /// drop bomb
    }
}

void PhysicalFormComponent::work(int ms)
{
    if(!_static)
    {
        if(_v >= 0.00001)
        {
            double  mx = cos(_angle) * _v / 1000.0 * ms,
                    my = sin(_angle) * _v / 1000.0 * ms;
            moveBy(mx,my);
            printPos();
        }
       // else printf("not moving\n");
    }
   // else printf("static\n");
}
SDL_Rect PhysicalFormComponent::rect(int ms)
{
    SDL_Rect rect = {.x = _x, .y = _y, .w = _w, .h = _h};
    rect.x += cos(_angle) * _v / 1000.0 * ms;
    rect.y += sin(_angle) * _v / 1000.0 * ms;
    return rect;
}

