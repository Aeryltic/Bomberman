#include "ObjectInstance.h"

ObjectInstance::ObjectInstance(const Object &base) : _base(base)
{
    _parent = nullptr;
}

ObjectInstance::~ObjectInstance()
{
    //dtor
}

void ObjectInstance::update(int time_passed)
{
    update_position(time_passed);
    /* update speed somehow */
}

void ObjectInstance::update_position(int time_passed)
{
    _posX += _vX / (1000.0) * time_passed;
    _posY += _vY / (1000.0) * time_passed;
}

double ObjectInstance::posX()
{
    double result = _posX;
    if(_parent)result += _parent->posX();
    return result;
}

double ObjectInstance::posY()
{
    double result = _posY;
    if(_parent)result += _parent->posY();
    return result;
    // return _posY + ((_parent)?(_parent->posY()):(0));
}
