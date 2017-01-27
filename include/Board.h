#ifndef BOARD_H
#define BOARD_H

#include <AbstractObject.h>
#include "Field.h"
#include <vector>
using namespace std;

class Board : public AbstractObject
{
    public:
        Board();
        virtual ~Board();
        ObjectType type(){return OBJECT_BOARD;}
        Field *field(int y, int x){return _field[y][x];}
        virtual int width(){return _w;}
        virtual int height(){return _h;}
    protected:

    private:
        int _w, _h;
        vector< vector<Field*> > _field;
};

#endif // BOARD_H
