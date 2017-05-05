#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include "Structures.h"
#include <SDL.h>
#include <memory>
#include "Constants.h"
#include <unordered_map>
#include "Enumerations.h"
#include "Typedefs.h"

class EntityManager;

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

class PhysicalForm : public Component // oddzieliæ kwestie zwi¹zane z ruchem od tego - stworzyæ MovementComponent
{
    /// tylko pozycja(w tym obroty) i kształt. pewnie będzie współpracować z jakimś MovementComponent(który chyba też nie powinien być jeden, ale powinien mieć klasy pochodne,
    ///                                                                                               albo jakiś kontroler, który determinuje to w jaki sposób się porusza)
    /// ważne żeby zrobić to raz a dobrze

    public:
        PhysicalForm() {} // to nie powinno tu byæ
        PhysicalForm(double x, double y, double z, double w, double h, double maxV = 50, double acc = 80)
            : Component(), _x(x), _y(y), _z(z), _w(w), _h(h), _angle(0) {}
        virtual ~PhysicalForm() {}

        void setZ(double z){_z = z;}
        double getZ(){return _z;}

        SDL_Rect rect(int ms = 0);
        double getAngle(){return _angle;}

        vector2d getPos(){return vector2d(_x,_y);}
        int_vector2d getGridPos(){return int_vector2d(round(_x/GRID_SIZE),round(_y/GRID_SIZE));} // instant crash with +0.5
        double getW(){return _w;}
        double getH(){return _h;}

    protected:
        void work(int ms);

    private:

        double _x, _y;
        double _z; // wysokosc uzywana narazie tylko w renderowaniu
        double _w, _h;
        double _angle; // chociaż też chyba nie powinien być tu
};
/// dodać AnimationComponent
class TextureComponent : public Component /// uses PhysicalForm
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

#endif // COMPONENT_H
