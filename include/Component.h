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
        bool _active;

    private:

        /// taki pomysl na optymalizacje, ale czy to rozsadne? - juz odpowiadam: to nie zadziala tak jak bys chcial
        //static vector<int> _user;
};

class LifeComponent : public Component /// to indicate that if dies should be removed or something - should be handled externally (using events or sth)
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
        PhysicalFormComponent(double x, double y, double w, double h, double maxV) : Component(), _x(x), _y(y), _w(w), _h(h), _maxV(maxV) {_v = 0; _angle=0; _z = 0;}
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

        SDL_Rect rect(int ms);

    protected:
        void work(int ms);

    private:
        //Vector2D _position;
        bool _solid;
        bool _static;

        double _x, _y;
        int _z; // wysokosc uzywana w renderowaniu
        double _maxV, _v, _angle;
        double _w, _h;
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

class PCControllerComponent : public Component /// uses PhysicalFormComponent
{
    public:
        PCControllerComponent(InputManager *iManager) : Component() {_iManager = iManager;}
        virtual ~PCControllerComponent() {}

        void setActive();

    protected:
        void work(int ms);

    private:
        InputManager *_iManager;

};

class NPCControllerComponent : public Component /// uses MovementComponent
{
    NPCControllerComponent() : Component() {_hasDestination = false;}
    Vector2D _dest;
    bool _hasDestination;
};

class Dangerous : public Component
{

};

#endif // COMPONENT_H
