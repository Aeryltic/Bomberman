#include "ObjectInstanceContainer.h"

ObjectInstanceContainer::ObjectInstanceContainer(ObjectContainer &objContainer) : _objContainer(objContainer)
{
    //ctor
}

ObjectInstanceContainer::~ObjectInstanceContainer()
{
    //dtor
}
bool ObjectInstanceContainer::createInstance(string type, int x, int y)
{
    if(type == "PLAYER")
    {
        _ins[_ins.size()] = PlayerInstance(_objContainer.getPlayer(), x, y);
    }
    if(type == "ENEMY")
}
