#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include "Structures.h"
#include <SDL.h>
#include <memory>
#include "Constants.h"
#include <unordered_map>
#include "Enumerations.h"

class EntityManager;
class ObjectFactory;

class Entity;
class InputManager;

using namespace std;

class Component
{
    public:
        Component() { _active = false;}
        //Component(Entity *target) : _target(target), _active(false) {}
        virtual ~Component() {}

        void update(int ms) {if(_active)work(ms);}

        virtual bool isActive() const {return _active;}
        virtual void setActive() {/*printf("Component::setActive()\n");*/_active = true;}
        virtual void setTarget(entity_ptr target){_target = target; setActive();}

        entity_ptr target(){return _target.lock();}

    protected:
        virtual void work(int ms) { }

        weak_ptr<Entity> _target;
        // unsigned long long _ownerID;
        bool _active;

    private:

       /// static unordered_multimap<Component,Component> *_store;
       /// klucz musi byc jeden dla kazdego rodzaju komponentu
};

class Alive : public Component /// to indicate that if dies should be removed or something - should be handled externally (using events or some system)
{
    public:
        Alive() {_alive = true;_AliveCount++;}
        virtual ~Alive() {_AliveCount--;}
        //static int getCount(){return _count;}
    private:
        bool _alive;
        int _type;

       // static int _count;
    /// SYSTEM NEEDED
};

class PhysicalFormComponent : public Component
{
    public:
        PhysicalFormComponent() {}
        PhysicalFormComponent(double x, double y, int z, double w, double h, double maxV = 50, double acc = 80)
            : Component(), _x(x), _y(y), _z(z), _w(w), _h(h), _maxV(maxV), _a(acc)
            {_v = 0; _angle=0; _destructible = false; _solid = false; _updated = false;}
        virtual ~PhysicalFormComponent() {}

        void moveTo(double x, double y){_x = x; _y = y;}
        void moveBy(double dx, double dy){_x += dx; _y += dy;}

        void printPos() const {printf("%.2lf x %.2lf\n",_x,_y);}

        void setMovable() {_static = false;}
        void setStatic() {_static = true;}


        void setMaxSpeed(double maxV) {_maxV = maxV;}

        void setSpeed(double v) {_v = v;}
        void setAngle(double a) {_angle = a;}
        void setSpeedToMax() {_v = _maxV;}

        void setZ(int z){_z = z;}
        int getZ(){return _z;}

        SDL_Rect rect(int ms = 0);
        double getAngle(){return _angle;}

        vector2d getPos(){return vector2d(_x,_y);}
        int_vector2d getGridPos(){return int_vector2d(round(_x/GRID_SIZE),round(_y/GRID_SIZE));} // instant crash with +0.5
        double getW(){return _w;}
        double getH(){return _h;}

        void setSolid(bool s){_solid = s;}

        void needsUpdate(){_updated = false;}

        void accelerate(int ms) {_v += _a * ms / 1000.0; if(_v > _maxV) _v = _maxV;}
        void deccelerate(int ms) {_v -= 2 * _a * ms / 1000.0; if(_v < 0.0) _v = 0.0;}

        void setDestructible(bool d) {_destructible = d;}
        bool isDestructible(){return _destructible;}

    protected:
        void work(int ms);

    private:
        //vector2d _position;
        bool _solid;
        bool _static;
        bool _destructible;
        bool _updated;

        double _x, _y;
        int _z; // wysokosc uzywana narazie tylko w renderowaniu
        double _w, _h;
        double _maxV, _v, _angle;
        double _a; // acceleration pixels/(s^2)
};
/*
class MovementComponent : public Component /// uses PhysicalFormComponent
{
    public:
        MovementComponent() {_maxV = 50.0; _v = 0.0; _angle = 0.0; setActive();}
        MovementComponent(double maxV) {_maxV = maxV; _v = 0.0; _angle = 0.0; setActive();}
        virtual ~MovementComponent() {}
        void work(int ms);


    private:

};
*/
class TextureComponent : public Component /// uses PhysicalFormComponent
{
    public:
        TextureComponent(SDL_Texture *texture) : _texture(texture) {_source = nullptr;}
        TextureComponent(SDL_Texture *texture, SDL_Rect *source) : _texture(texture), _source(source) {}
        virtual ~TextureComponent() {}

        SDL_Texture *texture() {return _texture;}
    private:
        SDL_Texture *_texture;
        SDL_Rect *_source;
};

class SolidComponent : public Component /// uses PhysicalFormComponent, sets collisions
{
    public:
        SolidComponent() {}
        virtual ~SolidComponent() {}
    /// SYSTEM NEEDED
};

class Dangerous : public Component /// enemies will flee away from tiles with this component
{

};

class Timer : public Component
{
    public:
        Timer(int timer) : Component(), _msLeft(timer) {}
        ~Timer(){}
        bool timeIsUp(){return _msLeft <= 0;}
    protected:
        void work(int ms) {_msLeft-=ms;}
    private:
        int _msLeft;
};

class NavNode : public Component    /// uses PhysicalFormComponent
{
    public:
        NavNode() : Component() {}
        ~NavNode() {}
        vector2d coor();
        NavNode *getNeighbour(int dir);
        void setLink(int dir, NavNode *node);
        // vector<NavNode *> v // neighbouring vertexes // not gut ajdija, to powinien zalatwiac system... chociaz moze...
    unordered_map<int, NavNode*> _linked; // int = Direction (do nawigacji)
};

class SquareCell : public Component /// powinny byc przetwarzane jako instancje - za duza redundancja
{
    public:
        SquareCell(WorldCellType type = CELL_NONE) : Component() {_type = type;}
        ~SquareCell() {}
        void setType(WorldCellType type){_type = type;}
        WorldCellType getType(){return _type;}
    private:
        WorldCellType _type;
};

class World : public Component
{
    public:
        World(int w, int h) : Component(), _w(w), _h(h) {_square.resize(_h); for(int i=0;i<_h;i++)_square[i].resize(_w);}
        ~World() {}

        void setup();
        bool addCell(entity_ptr cell);//, int x, int y);
        bool replace(entity_ptr cell);

        bool valid(int x, int y){ return ((x>=0) && (x<_w) && (y>=0) && (y<_h));}
        vector2d getNearestCellCoorFromGivenPosInGivenDirection(vector2d pos, int dir);

        entity_ptr getCell(int x, int y){if(valid(x,y))return _square[y][x]; return nullptr;}

        bool isDangerous(int x, int y);

        void destroyDirt(int x, int y, EntityManager *entityManager, ObjectFactory *objectFactory);
    private:
        int _w, _h;
        vector<vector<entity_ptr>> _square;
};

class PlayerControllerComponent : public Component /// uses PhysicalFormComponent
{
    public:
        PlayerControllerComponent(InputManager *iManager) : Component() {_iManager = iManager;}
        virtual ~PlayerControllerComponent() {}
        void setTarget(entity_ptr target){/*printf("PlayerControllerComponent::setTarget()\n");*/_target = target; setActive();}
        void setActive();

    protected:
        void work(int ms);
    private:
        InputManager *_iManager;

};

class KeyboardController : public Component /// uses PhysicalFormComponent
{
    public:
        KeyboardController(InputManager *iManager) : Component() {_iManager = iManager;}
        virtual ~KeyboardController() {}
        void setTarget(entity_ptr target){_target = target; setActive();}
        void setActive();

        InputManager *getInputManager() {return _iManager;}
    protected:
        void work(int ms);
    private:
        InputManager *_iManager;

};

class MovementController : public Component
{
    public:
        MovementController() : Component() {_physicalForm = nullptr;}
        ~MovementController() {}
        void setTarget(entity_ptr target){/*printf("MovementController::setTarget()\n");*/_target = target; MovementController::setActive();}
        //void setDest(NavNode *dest) { _dest = dest;} /// wrong
        void setActive();

        // when active ....
        vector2d current();

        void work(int ms);

        void setDest(vector2d dest);// {_dest = dest;}
        bool destReached();

       // void setDest(int dir);



   //     void setCurrent(NavNode *node){ _current = _dest = node;} /// wrong
    private:

        //NavNode *_dest; /// wrong
        //NavNode *_current; /// wrong
        vector2d _dest; /// ok
        PhysicalFormComponent *_physicalForm;

        bool _readyToStop;
        bool _reached;
        bool _moving;
 //       bool _moving;
};

class NPCControllerComponent : public Component /// uses PhysicalFormComponent
{
    public:
        NPCControllerComponent() : Component() {_hasDestination = false;}
    protected:
        void work(int ms);
    private:
        vector2d _dest;
        bool _hasDestination;
};

class AIController : public Component
{
    public:
        AIController() : Component() {}
        ~AIController() {}
        void setDir(int dir){_dir = dir;}
        int getDir(){return _dir;}
    private:
        int _dir;
};

class BombPlanter : public Component
{
    public:
        BombPlanter() : Component() {_lastPlant = 0;}
        ~BombPlanter() {}
        bool canPlantNext() {return(SDL_GetTicks() - _lastPlant > 3000); }
        void plant() {_lastPlant = SDL_GetTicks();}

    private:
        unsigned _lastPlant;
};

class Explosive : public Component
{
    public:
        Explosive(int range) : Component(), _range(range) {}
        ~Explosive() {}
        int getRange() {return _range;}
        void setRange(int range) {_range = range;}
    private:
        int _range;
};

class Destroyer : public Component
{
    public:
        Destroyer() : Component() {_done = false;}
        ~Destroyer() {}
        void done(){_done = true;}
        bool isDone(){return _done;}
    private:
        bool _done;
};

class Player : public Component
{
    public:
        Player() : Component() {}
        ~Player();
    private:
};

class Enemy : public Component
{
    public:
        Enemy() : Component() {_count++;}
        ~Enemy();

    private:
        static int _count;
};
#endif // COMPONENT_H
