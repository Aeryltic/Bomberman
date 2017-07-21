#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "Entity.h"

#include "Component.h"
#include "Structures.h"
#include "Enumerations.h"

#include <stack>
#include <deque>
#include <algorithm>

#include <SDL.h> /// tego tu być nie winno

struct CTransform : public Component {
    vec3d pos;
    vec3d vol; /// to stąd wywalić i dodać raczej scale, czy coś
    vec3d rot;
    weak_ptr<CTransform> parent;

    explicit CTransform(double x, double y, double z, double w, double h, double d = 0)
        : pos(x, y, z), vol(w, h, d), rot(0,0,0) { }
    explicit CTransform(const vec3d& pos, const vec3d& vol, const vec3d& rot)
        : pos(pos), vol(vol), rot(rot) { }
    virtual ~CTransform() {/*printf("pf_destr\n");*/}

    vec3d get_pos() const {return pos;}
    double get_r() const {return vol.x/2;}
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------
/// to jest uzasadnione żeby trzymać pojemnik tych jointów...
struct Joint {
    //weak_ptr<CTransform> parent;
    vec3d pos;
};

struct CJoints : public Component {
    vector<std::shared_ptr<Joint>> joints;
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------
/// ... ale to? to chyba inaczej powinno działać
/// to chyba w tej formie nie jest takie do końca super, bo wszystko może być instrumentem (tzn. powinno być)
struct CInstrument : public Component { /// to będzie w obiekcie, który może być "instrumentem", definiuje jego własności jako instrumentu
//    LuaRef handle;
};
/// to poniżej powinno być częścią jakiejś innej klasy, która już tych intrumentów używa - tego niskiego AI czy coś
struct CInstrumentHandler : public Component { /// to te "intrumenty" mają odpowiadać za wykonywanie akcji. i znowu - jedno Entity, dowolna ilość intrumentów
    vector<std::weak_ptr<CInstrument>> instruments;
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------
struct CRigidBody : public Component {
    double r; // okrąg/sfera

    CRigidBody(double r) : r(r) {}
};

/// Animation/SpriteComponent? Model+Texture+Skeleton+Animation
struct CAspect : public Component { // uses CPhysicalForm
    SDL_Color base_color;
    SDL_Color color;

    CAspect(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
        this->color = {.r=r,.g=g,.b=b,.a=a};
        this->base_color = {.r=r,.g=g,.b=b,.a=a};
    }
    CAspect(SDL_Color color) {
        this->color = color;
        this->base_color = color;
    }
    virtual ~CAspect() {}

    void set_color(Uint8 r, Uint8 g, Uint8 b) {
        this->color.r = r;
        this->color.g = g;
        this->color.b = b;
    }

    void reset_color() {
        color.r = base_color.r;
        color.g = base_color.g;
        color.b = base_color.b;
        color.a = 255;
    }
};

struct CDynamicBody : public Component { /// na razie traktowany jako punkt materialny
    double mass;
    vec3d net_force;
    vec3d speed; /// CKinematicBody?

};

struct CMovement : public Component {
    double max_speed;   /// czy to tu w ogóle powinno być?
    vec3d speed;

    explicit CMovement(double max_speed) : speed(0,0,0) {
        this->max_speed = max_speed;
    }
    virtual ~CMovement() {};
    /*
        void set_speed(double x, double y, double z) {
            speed = {x, y, z};
        }
        */
    vec3d get_speed() const { return speed;}
    void set_speed(vec3d speed) {
        this->speed = speed;
    }
    void stop() {
        speed = {0,0,0};
    }

    double get_max_speed() const {return max_speed;}
    void set_max_speed(double new_speed) {max_speed = new_speed;}
};

struct CActionTarget : public Component { /// to nie jest chyba dobry pomysł (nie lubię tego komponentu)
    string target_type;

    CActionTarget(string target_type) {
        this->target_type = target_type;
    }
    virtual ~CActionTarget() {
        remove_target(target_type, owner);
    }

    // Override
    void set_owner(std::weak_ptr<Entity> owner) {
        this->owner = owner;
        targets[target_type].push_back(owner);
    }

    // static
    static unordered_map<string, vector<weak_ptr<Entity>>> targets;

    static void remove_target(string s, weak_ptr<Entity> target) {
        auto it  = find_if(targets[s].begin(), targets[s].end(), [&target](const weak_ptr<Entity>& p) {return target.lock().get() == p.lock().get();});
        if(it != targets[s].end()) {
            targets[s].erase(it);
        }
    }

    static std::weak_ptr<Entity> closest_target(std::string target_name, Entity* entity);
};


struct CEnergyStore : public Component {
    double amount;
    double pace;

    CEnergyStore(double pace) {
        this->pace = pace;
        amount = 100.0;
    }
    virtual ~CEnergyStore() {};

    void set_amount(double amount) {this->amount = amount;}
    double get_amount() const { return amount; }
};

struct CBreeder : public Component { /// zamiast tego - akcja ze skryptem zwracającym czy można rodzić
    string child_type;
    double required_energy;
    int min_amount, max_amount;

    CBreeder(string child_type, double required_energy, int min_amount, int max_amount) {
        this->child_type = (child_type);
        this->required_energy = (required_energy);
        this->min_amount = (min_amount);
        this->max_amount = (max_amount);
    }
    virtual ~CBreeder() {};

    bool ready() {
        CEnergyStore *es = owner.lock()->get<CEnergyStore>();
        return (es && es->amount >= required_energy);
    }
};

struct CNeeds : public Component {
    double thirst;
    double hunger;
    double weariness;

    CNeeds(double thirst, double hunger, double weariness) : thirst(thirst), hunger(hunger), weariness(weariness) {}

    double get_thirst() const { return thirst; }
    double get_hunger() const { return hunger; }
    double get_weariness() const { return weariness; }

    void set_thirst(double v) { thirst = v; }
    void set_hunger(double v) { hunger = v; }
    void set_weariness(double v) { weariness = v; }
};

struct CAbstractObjectContainer : public Component {
    std::unordered_map<string, double> items;

    CAbstractObjectContainer() {}
    virtual ~CAbstractObjectContainer() {}

    void set_item(std::string name, double v) {
        items[name] = v;
    }
    double get_item(std::string name) {
        return items[name];
    }
};

struct CProperties : public Component {
    std::unordered_map<string, double> prop;

    CProperties() {
        prop["condition"] = 100;    // może być ale to nie do końca fajne jest
    }
    virtual ~CProperties() {}

    void set(std::string name, double v) {
        prop[name] = v;
    }
    double get(std::string name) {
        return prop[name];
    }
};

#endif // COMPONENTS_H
