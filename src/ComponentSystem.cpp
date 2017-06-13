#include "ComponentSystem.h"

#include "EntityManager.h"
#include "Views.h"
#include "GoapAgent.h"
#include "GoapPlanner.h"

#include "StringIndexer.h"

#include <algorithm>

void ComponentSystem::update(int timestep, EntityManager *entityManager) {
    for(auto &p : ufunctions) {
        p.second(timestep, entityManager);
    }
}

void ComponentSystem::addUpdateFunction(int priority, update_function ufunction) {
    auto p = make_pair(priority, ufunction);
    auto it = std::lower_bound(ufunctions.begin(), ufunctions.end(), p, [](pair<int, update_function> a, pair<int, update_function> b) -> bool{return a.first < b.first;});
    ufunctions.emplace(it, p);
}

bool ComponentSystem::init() {
    /// jakiś tam ruch
    addUpdateFunction(1, [](int ms, EntityManager* entityManager) /// tylko test
    {
        vector<MovementView> views = ViewCreator::createViews<MovementView>(entityManager);
        for(auto &v: views)
        {
            v.pf->pos += v.m->speed;
        }
    });

    /// breedery - to też AI, chociaż może nie nadużywajmy AI, to jest zwykły automat... ale jakieś metaautomaty też można by zrobić
    addUpdateFunction(20, [](int ms, EntityManager* entityManager) {
        vector<BreederView> views = ViewCreator::createViews<BreederView>(entityManager);
        for(auto &view: views) {
            if(view.breeder->ready()) {
                view.energy->amount -= view.breeder->required_energy;
                int amount = rand()%(view.breeder->max_amount - view.breeder->min_amount) + view.breeder->min_amount;
                while(amount--) {
                    vec3d p = random_point_in_range(view.pf->pos.x, view.pf->pos.y, view.pf->vol.x/2, view.pf->vol.x*2);
                    entityManager->make_object(StringIndexer::get_id(view.breeder->child_type), p.x, p.y);
                }
            }
        }
    });

    /// odnawianie energii
    addUpdateFunction(30, [](int ms, EntityManager* entityManager) {
        vector<EnergyView> views = ViewCreator::createViews<EnergyView>(entityManager);
        for(auto &view: views) {
            view.energy->amount += view.energy->pace * ms / 1000.0;
        }
    });

    /// AI - raczej na samym końcu...
    addUpdateFunction(100, [](int ms, EntityManager* entityManager) {
        for(auto &wagent: entityManager->get_components()[tindex(GoapAgent)]) {
            if(!wagent.second.expired()) {
                GoapAgent* agent = static_cast<GoapAgent*>(wagent.second.lock().get());
                agent->update(ms);
            }
        }
    });




    /// kolizje
    /*
    addUpdateFunction(50, [](int ms, EntityManager* entityManager)
    {
        for(auto &wpf: entityManager->getComponents()[tindex(CPhysicalForm)])   /// trzeba było zostawić na indeksach
        {
            CPhysicalForm *pf = static_cast<CPhysicalForm*>(wpf.lock().get());
            if(!(pf->owner.lock()->has<CMovement>())) continue; /// badamy z perspektywy poruszających się, to tak nie dokońca jest fajne; poprawka - to jest do dupy, bo każdy z każdym poruszającym testuje się dwa razy
            for(auto &wpf2: entityManager->getComponents()[tindex(CPhysicalForm)])
            {
                CPhysicalForm *pf2 = static_cast<CPhysicalForm*>(wpf2.lock().get());
                if(pf == pf2)continue;
                if(pf->pos.dist(pf2->pos) < (pf->vol.x + pf2->vol.x) / 2)   /// jeśli koliza to coś
                {
                    pf->owner.lock()->receive_message(Message{.type=MSG_COLLISION, pf2->owner});
                    pf2->owner.lock()->receive_message(Message{.type=MSG_COLLISION, pf->owner});
                }
            }
        }
    });
    */

    /// przesuwanie carryablów na parentów - to w ogóle też jest do dupy
    /*
    addUpdateFunction(50, [](int ms, EntityManager* entityManager)
    {
        for(auto &component: entityManager->getComponents()[tindex(CCarryable)])
        {
            CCarryable *carryable = static_cast<CCarryable*>(component.lock().get());
            if(!carryable->parent.expired())
            {
                CPhysicalForm *pfo = carryable->owner.lock()->get<CPhysicalForm>();
                CPhysicalForm *pfp = carryable->parent.lock()->get<CPhysicalForm>();
                if(pfo && pfp)
                {
                    pfo->pos = pfp->pos;
                }
            }
        }
    });*/

    /*
    /// oddziaływanie zapachów na węch
    addUpdateFunction(40, [](int ms, EntityManager* entityManager)
    {
        vector<ScentView> scent_views = ViewCreator::createViews<ScentView>(entityManager);
        vector<SmellSensorView> smell_views = ViewCreator::createViews<SmellSensorView>(entityManager);
        for(auto &scent: scent_views)
        {
            const unsigned &type = scent.scent->type;
            //printf("scnt ");
            vec3d &scent_pos = scent.pf->pos;
            for(auto &nose: smell_views)
            {
                //printf("nose ");
                vec3d &nose_pos = nose.pf->pos;
                nose.smell->stimuli[type].push(nose_pos.dist(scent_pos));
    //                printf()
            }
        }
    });

    /// przetwarzanie zapachów - to pewnie da się jakoś uogólnić
    addUpdateFunction(50, [](int ms, EntityManager* entityManager)
    {
        for(auto &smell: entityManager->getComponents()[tindex(CSmellSensor)])
        {
            CSmellSensor *sensor = static_cast<CSmellSensor*>(smell.lock().get());
            GoapAgent *ai = sensor->owner.lock()->get<GoapAgent>();
            if(ai)
            {
                for(auto &stimulant_p : sensor->stimuli)
                {

    //                    auto &stimulant = stimulant_p.second;
    //                    unsigned smell_type = stimulant_p.first;
    //
    //                    if((smell_type == ai->followed_scent) && (!stimulant.empty()))
    //                    {
    //                        //printf("stim ");
    //                        double curr = stimulant.top();
    //                        stimulant.pop();
    //                        while(!stimulant.empty()) {
    //
    //                            curr = (curr < stimulant.top()) ? stimulant.top() : curr;
    //                            stimulant.pop();
    //                        }
    //                       // if(sensor->last[smell_type] >= 0)
    //                        {
    //                            //printf("c ");
    //
    //                            if(curr < sensor->last[smell_type]) { /// to w ogóle o kant dupy rozbić
    //                                sensor->owner.lock()->receive_message(Message{.type=MSG_GOOD_DIRECTION, sensor->owner});
    //                            }
    //                            else sensor->owner.lock()->receive_message(Message{.type=MSG_BAD_DIRECTION, sensor->owner});
    //
    //                        }
    //                        sensor->last[smell_type] = curr;
    //                    }
    //                    else sensor->last[smell_type] = -1;

                }
            }
            for(auto &stimulant_p : sensor->stimuli)
            {
                while(!stimulant_p.second.empty())stimulant_p.second.pop();
            }
            //printf("nose: %d, ", int(sensor->stimuli.empty()));

        }
    });
    */
    return 0;
}
