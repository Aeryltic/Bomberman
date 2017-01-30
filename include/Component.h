#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include "Structures.h"
#include <SDL.h>
#include <memory>
#include "Constants.h"

class Entity;
class InputManager;

using namespace std;

class Component
{
    public:
        Component() {_target = nullptr; _active = false;}
        Component(Entity *target) : _target(target), _active(false) {}
        virtual ~Component() {}

        void update(int ms) {if(_active)work(ms);}

        virtual bool isActive() const {return _active;}
        virtual void setActive() {_active = true;}
        virtual void setTarget(entity_ptr target){_target = target; setActive();}

    protected:
        virtual void work(int ms) { }

        entity_ptr _target;
        // unsigned long long _ownerID;
        bool _active;

    private:

       /// static unordered_multimap<Component,Component> *_store;
       /// klucz musi byæ jeden dla kazdego rodzaju komponentu
};

class LifeComponent : public Component /// to indicate that if dies should be removed or something - should be handled externally (using events or some system)
{
    public:
        LifeComponent() {_alive = true;}
        virtual ~LifeComponent() {}
    private:
        bool _alive;
    /// SYSTEM NEEDED
};

class PhysicalFormComponent : public Component
{
    public:
        PhysicalFormComponent() {}
        PhysicalFormComponent(double x, double y, double w, double h, double maxV)
            : Component(), _x(x), _y(y), _w(w), _h(h), _maxV(maxV)
            {_v = 0; _angle=0; _z = 0; _destructible = false; _solid = false;}
        virtual ~PhysicalFormComponent() {}

        void moveTo(double x, double y){_x = x; _y = y;}
        void moveBy(double dx, double dy){_x += dx; _y += dy;}
        void printPos() const {printf("%.2lf x %.2lf\n",_x,_y);}

        void setMovable() {_static = false;}
        void setStatic() {_static = true;}
        void setDestructible(bool d) {_destructible = d;}

        void setMaxSpeed(double maxV) {_maxV = maxV;}
        void setSpeed(double v) {_v = v;}
        void setAngle(double a) {_angle = a;}
        void setSpeedToMax() {_v = _maxV;}

        void setZ(int z){_z = z;}
        int getZ(){return _z;}

        SDL_Rect rect(int ms);
        double getAngle(){return _angle;}

        Vector2D getPos(){return Vector2D(_x,_y);}
        double getW(){return _w;}
        double getH(){return _h;}

        void setSolid(bool s){_solid = s;}

    protected:
        void work(int ms);

    private:
        //Vector2D _position;
        bool _solid;
        bool _static;
        bool _destructible;

        double _x, _y;
        double _w, _h;
        double _maxV, _v, _angle;
        int _z; // wysokosc uzywana w renderowaniu
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

class PlayerControllerComponent : public Component /// uses PhysicalFormComponent
{
    public:
        PlayerControllerComponent(InputManager *iManager) : Component() {_iManager = iManager;}
        virtual ~PlayerControllerComponent() {}

        void setActive();

    protected:
        void work(int ms);
    private:
        InputManager *_iManager;

};

class NPCControllerComponent : public Component /// uses PhysicalFormComponent
{
    public:
        NPCControllerComponent() : Component() {_hasDestination = false;}
    protected:
        void work(int ms);
    private:
        Vector2D _dest;
        bool _hasDestination;
};

class Dangerous : public Component /// enemies will flee away from tiles with this component
{

};

class TimerComponent : public Component
{
    public:
        TimerComponent(int timer) : Component(), _msLeft(timer) {}
        ~TimerComponent(){}
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
        Vector2D coor();
        // vector<NavNode *> v // neighbouring vertexes // not gut ajdija, to powinien zalatwiac system... chociaz moze...

};
#endif // COMPONENT_H
