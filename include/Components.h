#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "Entity.h"

#include "Component.h"
#include "Structures.h"
#include "Enumerations.h"

#include <stack>
#include <deque>
#include <algorithm>

//#include "ScriptSystem.h"

//using message_callback = function<void(Message &)>;
//namespace comp_setup {
//void register_components();
//}


struct CPhysicalForm : public Component {
    vec3d pos;
    vec3d vol;
    vec3d rot;

    explicit CPhysicalForm(double x, double y, double z, double w, double h, double d = 0)
        : pos(x, y, z), vol(w, h, d), rot(0,0,0) { }
    explicit CPhysicalForm(const vec3d& pos, const vec3d& vol, const vec3d& rot)
        : pos(pos), vol(vol), rot(rot) { }
    virtual ~CPhysicalForm() {/*printf("pf_destr\n");*/}
};

struct CRigidBody : public Component {
    double r;

    CRigidBody(double r) : r(r) {}
};

/// Animation/SpriteComponent?
struct CAspect : public Component { /// uses CPhysicalForm
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

    void set_color(Uint8 r, Uint8 g, Uint8 b){
        this->color.r = r;
        this->color.g = g;
        this->color.b = b;
    }

    void reset_color(){
        color.r = base_color.r;
        color.g = base_color.g;
        color.b = base_color.b;
        color.a = 255;
    }
};

struct CMovement : public Component {
    double max_speed;
    vec3d speed;

    explicit CMovement(double max_speed) : speed(0,0,0) {
        this->max_speed = max_speed;
    }
    virtual ~CMovement() {};

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
    //std::unordered_map<int, weak_ptr<Entity>> obj;
    unsigned grains;

    CAbstractObjectContainer() {grains = 0;}
    virtual ~CAbstractObjectContainer(){}

    unsigned get_grains() const {return grains;}
    void set_grains(unsigned v){grains = v;}
};

struct CParameterContainer : public Component {
    std::unordered_map<string, double> param;

    CParameterContainer() {}
    virtual ~CParameterContainer() {}
};

#endif // COMPONENTS_H
