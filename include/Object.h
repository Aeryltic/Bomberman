#ifndef OBJECT_H
#define OBJECT_H

#include <string>
using namespace std;
/** templates for in-game object instances */
class Object
{
    public:
        Object();
        virtual ~Object();
//        virtual void update(int time_passed);
    protected:

    private:
        string _name;
        // predkosc  w pikselach lub metrach na sekunde
};

#endif // OBJECT_H
