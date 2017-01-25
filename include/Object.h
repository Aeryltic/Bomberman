#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <unordered_map>
#include "Structures.h"
#include "Enumerations.h"
#include "Texture.h"

using namespace std;
/** templates for in-game object instances */

class Object
{
    public:
        Object();
        virtual ~Object();
        ObjectType type(){return _type;}
        virtual Texture* texture();
    protected:
        ObjectType _type;
        string _name;
    private:
     //   bool _printable;

    //    unordered_map<string, Variable> _var;
};

#endif // OBJECT_H
