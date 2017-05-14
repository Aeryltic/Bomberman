#ifndef VIEWS_H_INCLUDED
#define VIEWS_H_INCLUDED

#include "Components.h"
#include "Entity.h"

class ViewCreator
{
    public:
    template<class C>
    static vector<C> createViews(EntityManager *entityManager) /// na dłuższą metę i tak będzie trzeba robić osobny creator dla każdego widoku, bo to jest niewydajne
    {
        vector<C> views;
        for(auto &e : entityManager->getEntities())
        {
            C view(e.second.get());
            if(view.complete){
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
    MovementView(Entity *e)
    {
        pf = e->get<CPhysicalForm>();
        m = e->get<CMovement>();
        complete = (pf && m);
    }
    CPhysicalForm *pf;
    CMovement *m;
};

struct BreederView : View {
    BreederView(Entity *e)
    {
        breeder = e->get<CBreeder>();
        energy = e->get<CEnergyStore>();
        pf = e->get<CPhysicalForm>();

        complete = (breeder && energy && pf);
    }
    CBreeder *breeder;
    CEnergyStore *energy;
    CPhysicalForm *pf;
};

struct EnergyView : View {
    EnergyView(Entity *e)
    {
        energy = e->get<CEnergyStore>();

        complete = (energy);
    }
    CEnergyStore *energy;
};

#endif // VIEWS_H_INCLUDED
