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
void PCControllerComponent::update(int ms)
{
    if(_active)
    {
        // movement
        if(_iManager->keyStatus(SDLK_w) & (KEY_PRESSED|KEY_DOWN))
        {
            _target->getComponent<MovementComponent>()->setSpeedToMax();
            _target->getComponent<MovementComponent>()->setAngle(M_PI/2);
            /// go up
        }
        else if(_iManager->keyStatus(SDLK_s) & (KEY_PRESSED|KEY_DOWN))
        {
            _target->getComponent<MovementComponent>()->setSpeedToMax();
            _target->getComponent<MovementComponent>()->setAngle(M_PI*3/2);
            /// go down
        }
        else if(_iManager->keyStatus(SDLK_a) & (KEY_PRESSED|KEY_DOWN))
        {
            _target->getComponent<MovementComponent>()->setSpeedToMax();
            _target->getComponent<MovementComponent>()->setAngle(M_PI);
            /// go left
        }
        else if(_iManager->keyStatus(SDLK_d) & (KEY_PRESSED|KEY_DOWN))
        {
            _target->getComponent<MovementComponent>()->setSpeedToMax();
            _target->getComponent<MovementComponent>()->setAngle(0);
            /// go right
        }
        else _target->getComponent<MovementComponent>()->setSpeed(0);
        // bomb dropping
        if(_iManager->keyStatus(SDLK_SPACE) & (KEY_PRESSED))
        {
            /// drop bomb
        }
    }
    else printf("player controller not active\n");
}

void MovementComponent::update(int ms)
{
    if(_active)
    {
        if(_v >= 0.00001)
        {
            double  mx = cos(_angle) * _v / 1000.0 * ms,
                    my = sin(_angle) * _v / 1000.0 * ms;
            _target->getComponent<PhysicalFormComponent>()->moveBy(mx,my);
            _target->getComponent<PhysicalFormComponent>()->printPos();
        }
    }
}

