#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "Entity.h"

#include "Component.h"
#include "Structures.h"
#include "Enumerations.h"

#include <stack>
#include <deque>
using message_callback = function<void(Message &)>;
struct CPhysicalForm : public Component
{
    CPhysicalForm(weak_ptr<Entity> owner, double x, double y, double z, double w, double h, double d = 0)
        : Component(owner), pos(x, y, z), vol(w, h, d), rot(0,0,0)
    {
    }
    virtual ~CPhysicalForm() {}

    vec3d pos;
    vec3d vol;
    vec3d rot;
};

/// Animation/SpriteComponent?
struct CAspect : public Component /// uses CPhysicalForm
{
    //CAspect(weak_ptr<Entity> owner, SDL_Texture *texture, SDL_Rect *source) :  Component(owner), texture(texture), source(source) {}
    CAspect(weak_ptr<Entity> owner, SDL_Color color)
        :  Component(owner), color(color) {}
    virtual ~CAspect() {}

    SDL_Color color;
//    SDL_Texture *texture; /// tu chyba shared_ptr powinien być, a w GraphicsManagerze weak_ptr, albo jeszcze jakoś inaczej
//    SDL_Rect *source;

};

struct CMovement : public Component
{
    CMovement(weak_ptr<Entity> owner, float max_speed)
        : Component(owner)
    {
        this->max_speed = max_speed;
        //this->movement_angle = rand()%360;
    }
    virtual ~CMovement() {};

    //bool has_dest = false;
    //vec3d dest;
    //float movement_angle;
    //vec3d speed;            // to raczej w punktach na sekundę
    float max_speed;
    /// to potem gdzie indziej pójdzie
    //unsigned wait_end;
};

struct CActionTarget : public Component /// to nie jest chyba dobry pomysł
{
    CActionTarget(weak_ptr<Entity> owner, string target_type) : Component(owner), target_type(target_type)
    {
        targets[target_type].push_back(owner); /// może jakieś problemy przy wielowątkowości?
    }
    virtual ~CActionTarget(){}

    string target_type;

    static unordered_map<string, vector<weak_ptr<Entity>>> targets;
};

///-------------------------------------------------------------------------------------------
struct CSensor : public Component
{
    CSensor(weak_ptr<Entity> owner)
        : Component(owner)
    {
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
/// to sie chyba jeszcze wykorzysta
/*
struct CClosestTargetSensor : public CSensor
{
    CClosestTargetSensor(weak_ptr<Entity> owner) : CSensor(owner) {}
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
    CSmellSensor(weak_ptr<Entity> owner)
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
    CStimulusSource(weak_ptr<Entity> owner, float intensity)
        : Component(owner), intensity(intensity) {}
    virtual ~CStimulusSource() {};

    //float radius; /// to powinno być jakoś inaczej liczone
    float intensity; /// tylko to powinno tu być, radius liczony jakaś funkcją
};

struct CScentSource : public CStimulusSource
{
    CScentSource(weak_ptr<Entity> owner, float intensity, ScentType type)
        : CStimulusSource(owner, intensity), type(type) {}
    virtual ~CScentSource() {};

    ScentType type;
};
*/
///-------------------------------------------------------------------------------------------
struct CCarryable : public Component
{
    CCarryable(weak_ptr<Entity> owner): Component(owner)
    {
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

struct CEnergyStore : public Component
{
    CEnergyStore(weak_ptr<Entity> owner, float pace)
        : Component(owner), pace(pace)
    {
        amount = 100.0;
    }
    virtual ~CEnergyStore() {};

    float amount;
    float pace; /// to nie powinno tu być
};

struct CConsumable : public Component
{
    CConsumable(weak_ptr<Entity> owner, ConsumableType type, float value)
        : Component(owner), type(type), value(value)
    {
        owner.lock()->register_listener(MSG_COLLISION, [=](Message &msg)
        {
            msg.publisher.lock()->receive_message(Message{.type=MSG_IM_EDIBLE, owner});
        });
    }
    virtual ~CConsumable() {};

    ConsumableType type;
    float value;
};

struct CBreeder : public Component
{
    CBreeder(weak_ptr<Entity> owner, string child_type, float required_energy, int min_amount, int max_amount)
        : Component(owner), child_type(child_type), required_energy(required_energy),
          min_amount(min_amount), max_amount(max_amount) {}
    virtual ~CBreeder() {};

    string child_type;
    float required_energy;
    int min_amount, max_amount;

    bool ready()
    {
        CEnergyStore *es = owner.lock()->get<CEnergyStore>();
        return (es && es->amount >= required_energy);
    }
};

struct CBackpack : public Component
{
    CBackpack(weak_ptr<Entity> owner)
        : Component(owner)
    {
        /*
        owner.lock()->register_listener(MSG_IM_CARRYABLE, [=](Message &msg){
            items[msg.publisher.lock()->getID()] = msg.publisher;
            CCarryable *c = msg.publisher.lock()->get<CCarryable>();
            if(c) {
                c->parent = owner;
                /// tylko eksperyment, normalnie to to będzie jedno z Action
                auto ai = owner.lock()->get<GoapAgent>();
                if(ai)
                {
                    ai->followed_scent = SCENT_NEST;
                }
                /// -----------------
            }
            else printf("wtf, error... ");
        });
        */
    }
    virtual ~CBackpack() {};

    unordered_map<unsigned, weak_ptr<Entity>> items; /// szkoda tylko, że kilku może nosić to samo
};



/*
struct CNeeds : public Component
{
    CNeeds(weak_ptr<Entity> owner): Component(owner) {}
    virtual ~CNeeds(){};

    float   hunger, thirst, weariness,
            hungerV, thirstV, wearinessV;
};
*/

//struct CPosition : public Component
//{
//    CPosition(weak_ptr<Entity> owner, double x, double y, double z) : Component(owner), x(x), y(y), z(z) {}
//
//    double x, y, z;
//    double ax, ay, az;
//};

//struct CShape : public Component
//{
//     CShape(weak_ptr<Entity> owner) : Component(owner){}
//};

#endif // COMPONENTS_H
