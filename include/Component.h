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

        virtual void update(int ms) {}

        virtual bool isActive() const {return _active;}
        virtual void setActive() {_active = true;}
        virtual void setTarget(entity_ptr target){_target = target; setActive();}

    protected:
        entity_ptr _target;
        bool _active;


    private:

        /// taki pomysl na optymalizacje, ale czy to rozsadne? - juz odpowiadam: to nie zadziala tak jak bys chcial
        //static vector<int> _user;
};

class LifeComponent : public Component /// to indicate that if dies should be removed or something - should be handled externally (using events or sth)
{
    public:
        LifeComponent() {}
        virtual ~LifeComponent() {}
    /// SYSTEM NEEDED
};

class PhysicalFormComponent : public Component
{
    public:
        PhysicalFormComponent() {}
        PhysicalFormComponent(double x, double y, double w, double h) : _position(x,y), _w(w), _h(h) {}
        virtual ~PhysicalFormComponent() {}
        void moveTo(double x, double y){_position.x = x; _position.y = y;}
        void moveBy(double x, double y){_position.x += x; _position.y += y;}
        void printPos() {printf("%lf x %lf\n",_position.x,_position.y);}
    private:
        Vector2D _position;
        double _w, _h;
};

class MovementComponent : public Component /// uses PhysicalFormComponent
{
    public:
        MovementComponent() {_maxV = 50.0; _v = 0.0; _angle = 0.0; setActive();}
        MovementComponent(double maxV) {_maxV = maxV; _v = 0.0; _angle = 0.0; setActive();}
        virtual ~MovementComponent() {}
        void update(int ms);

        void setMaxSpeed(double maxV) {_maxV = maxV;}
        void setSpeed(double v) {_v = v;}
        void setAngle(double a) {_angle = a;}
        void setSpeedToMax() {_v = _maxV;}
    private:
        double _maxV, _v, _angle;
};

class TextureComponent : public Component /// uses PhysicalFormComponent
{
    public:
        TextureComponent(SDL_Texture *texture) : _texture(texture) {}
        virtual ~TextureComponent() {}
    private:
        SDL_Texture *_texture;
};

class SolidComponent : public Component /// uses PhysicalFormComponent, sets collisions
{
    public:
        SolidComponent() {}
        virtual ~SolidComponent() {}
    /// SYSTEM NEEDED
};

class PCControllerComponent : public Component /// uses MovementComponent
{
    public:
      //  PCControllerComponent() : Component() {_iManager = nullptr;}
        PCControllerComponent(shared_ptr<InputManager> iManager) : Component() {_iManager = iManager;}
        virtual ~PCControllerComponent() {}

        void update(int ms);
        //void setTarget(entity_ptr target){_target = target; _active = true;}

        //void setActive();
    protected:

    private:
        shared_ptr<InputManager> _iManager;
};

class NPCControllerComponent : public Component /// uses MovementComponent
{
    Vector2D _dest;
};

#endif // COMPONENT_H
