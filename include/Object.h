#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <unordered_map>
#include "Structures.h"
#include "Enumerations.h"
#include "Texture.h"
#include "Controller.h"
#include "GraphicsManager.h"
using namespace std;
/** templates for in-game object instances */
/// na razie beda jedynym rodzajem obiektow, jak bedzie czas oddzieli sie bazy od instancji

class Object
{
    public:
        Object();
        virtual ~Object();

        virtual SDL_Texture* texture() const {return nullptr;}
        virtual ObjectType type() const {return OBJECT_NONE;}
        virtual void update(int ms_passed) {if(_moving) updatePosition(ms_passed);}
        void updatePosition(int ms_passed) {_p.updatePosition(ms_passed);}
        void setSpeed(const Vector2D &v) {_p.v = v;}
        void setPos(const Vector2D &pos) {_p.pos = pos;}
        void stop(){_moving = false;}
        void start(){_moving = true;}
        virtual void setController(Controller *controller) {}
        virtual void* field(int y, int x) const {return nullptr;}

        virtual int width() const {return 0;}
        virtual int height()const {return 0;}
        virtual int z() const {return 0;}

//        static void setGraphicsManager(GraphicsManager *gManager){_gManager = gManager;}

        virtual SDL_Rect rect(int ms_passed = 0) const
        {
            SDL_Rect r;
            Vector2D v = _p.interpolated(ms_passed);
            r.w = width();
            r.h = height();

            return r;
        }
    protected:
   //     string _name;
        bool _moving;
        PositionAndSpeed _p;
    //    double _posX, _posY, _vX, _vY;
    private:
    //    static GraphicsManager *_gManager;

     //   bool _printable;

    //    unordered_map<string, Variable> _var;
};

#endif // OBJECT_H
