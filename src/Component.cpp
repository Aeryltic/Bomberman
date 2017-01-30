#include "Component.h"
#include "InputManager.h"
#include "Entity.h"
#include <cmath>

/// PhysicalFormComponent ---------------------------------------------------------------------------
void PhysicalFormComponent::work(int ms)
{
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
}
SDL_Rect PhysicalFormComponent::rect(int ms)
{
    SDL_Rect rect = {.x = _x, .y = _y, .w = _w, .h = _h};
    rect.x += cos(_angle) * _v / 1000.0 * ms;
    rect.y += sin(_angle) * _v / 1000.0 * ms;
    return rect;
}
/// PlayerControllerComponent ---------------------------------------------------------------------------

/*
void PlayerControllerComponent::setActive()
{
    if((_iManager != nullptr) && (_target->getComponent<MovementComponent>())) /// potrzebuje klawiatury i jego target musi umiec sie poruszac
    {
        _active = true;
    }
}
*/
void PlayerControllerComponent::setActive()
{
    if(_target->hasComponent<PhysicalFormComponent>() && (_iManager != nullptr))
        _active = true;
}
void PlayerControllerComponent::work(int ms)
{
    int up_down = 0,
        left_right = 0;
    if(_iManager->keyStatus(SDLK_w) & (KEY_PRESSED|KEY_DOWN))   // go up
    {
        up_down = -1;
    }
    else if(_iManager->keyStatus(SDLK_s) & (KEY_PRESSED|KEY_DOWN))  // go down
    {
        up_down = 1;
    }
    if(_iManager->keyStatus(SDLK_a) & (KEY_PRESSED|KEY_DOWN))  // go left
    {
        left_right = -1;
    }
    else if(_iManager->keyStatus(SDLK_d) & (KEY_PRESSED|KEY_DOWN))  // go right
    {
        left_right = 1;
    }

    if(up_down || left_right)
    {
        _target->getComponent<PhysicalFormComponent>()->setAngle(atan2(up_down,left_right));
        _target->getComponent<PhysicalFormComponent>()->setSpeedToMax();
    }
    else _target->getComponent<PhysicalFormComponent>()->setSpeed(0);
    // bomb dropping
    if(_iManager->keyStatus(SDLK_SPACE) & (KEY_PRESSED))    // drop bomb
    {
            /// DROP THAT BOMB
    }
}
/// NPCControllerComponent ---------------------------------------------------------------------------
void NPCControllerComponent::work(int ms)
{

}

Vector2D NavNode::coor()
{
    Vector2D v = _target->getComponent<PhysicalFormComponent>()->getPos();
    v.x += _target->getComponent<PhysicalFormComponent>()->getW()/2;
    v.y += _target->getComponent<PhysicalFormComponent>()->getH()/2;
    return v;
}

