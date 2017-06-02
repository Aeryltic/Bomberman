#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "Entity.h"

#include "Component.h"
#include "Structures.h"
#include "Enumerations.h"

#include <stack>
#include <deque>

#include "ScriptSystem.h"

//using message_callback = function<void(Message &)>;

void register_components(lua_State *L);

struct CPhysicalForm : public Component {
    explicit CPhysicalForm(double x, double y, double z, double w, double h, double d = 0)
        : pos(x, y, z), vol(w, h, d), rot(0,0,0) { }
    virtual ~CPhysicalForm() {}

    vec3d pos;
    vec3d vol;
    vec3d rot;
};

/// Animation/SpriteComponent?
struct CAspect : public Component { /// uses CPhysicalForm
    //CAspect(SDL_Texture *texture, SDL_Rect *source) : , texture(texture), source(source) {}
    CAspect(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
        this->color = {r,g,b,a};
    }
    CAspect(SDL_Color color) {
        this->color = (color);
    }
    virtual ~CAspect() {}

    SDL_Color color;
//    SDL_Texture *texture; /// tu chyba shared_ptr powinien być, a w GraphicsManagerze weak_ptr, albo jeszcze jakoś inaczej
//    SDL_Rect *source;

};

struct CMovement : public Component {
    CMovement(float max_speed) {
        this->max_speed = max_speed;
    }
    virtual ~CMovement() {};

    float max_speed;
};

struct CActionTarget : public Component { /// to nie jest chyba dobry pomysł
    CActionTarget(string target_type) {
        this->target_type = target_type;
    }
    virtual ~CActionTarget() {}

    // Override
    void set_owner(std::weak_ptr<Entity> owner) {
        this->owner = owner;
        targets[target_type].push_back(owner);
    }

    string target_type;
    static unordered_map<string, vector<weak_ptr<Entity>>> targets;
};


struct CEnergyStore : public Component {
    CEnergyStore(float pace) {
        this->pace = pace;
        amount = 100.0;
    }
    virtual ~CEnergyStore() {};

    float amount;
    float pace; /// to nie powinno tu być
};

struct CBreeder : public Component { /// zamiast tego - akcja ze skryptem zwracającym czy można rodzić
    CBreeder(string child_type, float required_energy, int min_amount, int max_amount) {
        this->child_type = (child_type);
        this->required_energy = (required_energy);
        this->min_amount = (min_amount);
        this->max_amount = (max_amount);
    }
    virtual ~CBreeder() {};

    string child_type;
    float required_energy;
    int min_amount, max_amount;

    bool ready() {
        CEnergyStore *es = owner.lock()->get<CEnergyStore>();
        return (es && es->amount >= required_energy);
    }
};
///-------------------------------------------------------------------------------------------
/*
struct CSensor : public Component
{
    CSensor() {
        owner.lock()->register_listener(MSG_SCANNING, [=](Message& msg)
        {
            scan();
        });
    }
    virtual ~CSensor() {};

    virtual void scan()
    {
        printf("default scan\n");
    }

    float effectiveness;
};
*/
/// to sie chyba jeszcze wykorzysta
/*
struct CClosestTargetSensor : public CSensor
{
    CClosestTargetSensor() : CSensor(owner) {}
    virtual ~CClosestTargetSensor() {};

    //string target_type;

    void scan(string target_type)
    {
        printf("looking for: %s\n", target_type.c_str());
        weak_ptr<Entity> closest;
        float dist = 0;
        auto opf = owner.lock()->get<CPhysicalForm>();
        if(opf)
        {
            for(auto target: CActionTarget::targets[target_type])
            {
                auto pf = target.lock()->get<CPhysicalForm>();
                if(pf)
                {
                    if(closest.expired())
                    {
                        closest = target;
                        dist = opf->pos.dist(pf->pos);
                    }
                    else
                    {
                        float temp = opf->pos.dist(pf->pos);
                        if(temp < dist)
                        {
                            closest = target;
                            dist = temp;
                        }
                    }
                }
            }
        }
        owner.lock()->receive_message(Message(MSG_TARGET, closest));
    }
};
*/
/*
struct CSmellSensor : public CSensor
{
    CSmellSensor()
        : CSensor(owner) {}
    virtual ~CSmellSensor() {};

    void scan()
    {
        printf("smell scan\n");
        //Entity *close
    }

    //unordered_map<unsigned, double> last; /// tego tu być nie winno, jeśli już to w CAIBlackboard
    //unordered_map<unsigned, stack<double>> stimuli;
};

struct CSightSensor : public CSensor
{

};
 // chyba jednak niepoczebne
struct CLifeSignsSensor : public CSensor
{

};

struct CStimulusSource : public Component /// czy to ma sens? dźwięki, zapachy... co jeszcze?
{
    CStimulusSource(float intensity)
        : intensity(intensity) {}
    virtual ~CStimulusSource() {};

    //float radius; /// to powinno być jakoś inaczej liczone
    float intensity; /// tylko to powinno tu być, radius liczony jakaś funkcją
};

struct CScentSource : public CStimulusSource
{
    CScentSource(float intensity, ScentType type)
        : CStimulusSource(owner, intensity), type(type) {}
    virtual ~CScentSource() {};

    ScentType type;
};
*/
///-------------------------------------------------------------------------------------------
/*
struct CCarryable : public Component
{
    CCarryable(): {
        parent.reset();
        owner.lock()->register_listener(MSG_COLLISION, [=](Message &msg)
        {
            if(parent.expired())/// już go kilku nie poniesie
            {
                msg.publisher.lock()->receive_message(Message{.type=MSG_IM_CARRYABLE, owner});
            }
        });
    }
    virtual ~CCarryable() {};

    weak_ptr<Entity> parent;
};


struct CConsumable : public Component
{
    CConsumable(ConsumableType type, float value) {
        this->type = type;
        this->value = value;
//        owner.lock()->register_listener(MSG_COLLISION, [=](Message &msg) {
//            msg.publisher.lock()->receive_message(Message{.type=MSG_IM_EDIBLE, owner});
//        });
    }
    virtual ~CConsumable() {};

    ConsumableType type;
    float value;
};
*/

/*
struct CBackpack : public Component
{
    CBackpack()
        :
    {
//        owner.lock()->register_listener(MSG_IM_CARRYABLE, [=](Message &msg){
//            items[msg.publisher.lock()->getID()] = msg.publisher;
//            CCarryable *c = msg.publisher.lock()->get<CCarryable>();
//            if(c) {
//                c->parent = owner;
//                /// tylko eksperyment, normalnie to to będzie jedno z Action
//                auto ai = owner.lock()->get<GoapAgent>();
//                if(ai)
//                {
//                    ai->followed_scent = SCENT_NEST;
//                }
//                /// -----------------
//            }
//            else printf("wtf, error... ");
//        });
    }
    virtual ~CBackpack() {};

    unordered_map<unsigned, weak_ptr<Entity>> items; /// szkoda tylko, że kilku może nosić to samo
};
*/


/*
struct CNeeds : public Component
{
    CNeeds(): {}
    virtual ~CNeeds(){};

    float   hunger, thirst, weariness,
            hungerV, thirstV, wearinessV;
};
*/

#endif // COMPONENTS_H
