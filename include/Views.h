#ifndef VIEWS_H_INCLUDED
#define VIEWS_H_INCLUDED

#include "Components.h"
#include "Entity.h"

#include "GoapAgent.h"

class ViewCreator {
public:
    template<class C>
    static vector<C> createViews(EntityManager *entityManager) { /// na dłuższą metę i tak będzie trzeba robić osobny creator dla każdego widoku, bo to jest niewydajne
        vector<C> views;
        for(auto &e : entityManager->get_entities()) {
            C view(e.second.get());
            if(view.complete) {
                views.push_back(view);
            }
        }
        return views;
    }
};

struct View {
    bool complete = false;
};

struct MovementView : View {
    MovementView(Entity *e) {
        pf = e->get<CTransform>();
        m = e->get<CMovement>();
        complete = (pf && m);
    }
    CTransform *pf;
    CMovement *m;
};

struct BreederView : View {
    BreederView(Entity *e) {
        breeder = e->get<CBreeder>();
        energy = e->get<CEnergyStore>();
        pf = e->get<CTransform>();

        complete = (breeder && energy && pf);
    }
    CBreeder *breeder;
    CEnergyStore *energy;
    CTransform *pf;
};

struct EnergyView : View {
    EnergyView(Entity *e) {
        energy = e->get<CEnergyStore>();

        complete = (energy);
    }
    CEnergyStore *energy;
};
/*
struct ScentView : View
{
    ScentView(Entity *e)
    {
        scent = e->get<CScentSource>();
        pf = e->get<CPhysicalForm>();

        complete = (scent && pf);
    }
    CScentSource *scent;
    CPhysicalForm *pf;
};

struct SmellSensorView : View
{
    SmellSensorView(Entity *e)
    {
        smell = e->get<CSmellSensor>();
        pf = e->get<CPhysicalForm>();

        complete = (smell && pf);
    }
    CSmellSensor *smell;
    CPhysicalForm *pf;
};
*/
struct AIView : View {
    AIView(Entity *e) {
        ai = e->get<GoapAgent>();
        pf = e->get<CTransform>();
        m  = e->get<CMovement>();

        complete = (ai && pf && m);     /// to wszystko tylko teraz tak wygląda
    }
    GoapAgent *ai;
    CTransform *pf;
    CMovement *m;
};

#endif // VIEWS_H_INCLUDED
