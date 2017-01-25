#include "Object.h"

Object::Object()
{
    _type = OBJECT_NONE;
 //   _printable = false;
}

Object::~Object()
{
    //dtor
}

Texture* Object::texture()
{
    return nullptr;
}
