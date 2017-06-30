#include "ComponentSystem.h"

#include <iterator>

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
    logs::open("initializing component systems...\n");

    /// jakiś tam ruch
    addUpdateFunction(1, [](int ms, EntityManager* entityManager) {
        vector<MovementView> views = ViewCreator::createViews<MovementView>(entityManager);
        for(auto &v: views) {
            //printf("moving by %s\n", v.m->speed.repr().c_str());
            //printf("pos: %s\n", v.pf->pos.repr().c_str());
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
                    vec3d p = view.pf->pos.random_in_range(view.pf->vol.x/2, view.pf->vol.x*2);
                    entityManager->make_object(view.breeder->child_type, p.x, p.y);
                }
            }
        }
    });

    /// odnawianie energii
    addUpdateFunction(30, [](int ms, EntityManager* entityManager) {
        double fraction = ms / 1000.0;
        vector<EnergyView> views = ViewCreator::createViews<EnergyView>(entityManager);
        for(auto &view: views) {
            view.energy->amount += view.energy->pace * fraction;
        }
    });

    /// needs
    addUpdateFunction(50, [](int ms, EntityManager* entityManager) {
        for(auto &p: entityManager->get_components()[tindex(CNeeds)]) {
            if(!p.second.expired()) {
                CNeeds* needs = static_cast<CNeeds*>(p.second.lock().get());
                needs->thirst += 0.1;
                needs->hunger += 0.05;
                needs->weariness += 0.1;
            }
        }
    });

    /// AI
    addUpdateFunction(100, [](int ms, EntityManager* entityManager) {
        for(auto &wagent: entityManager->get_components()[tindex(GoapAgent)]) {
            if(!wagent.second.expired()) {
                GoapAgent* agent = static_cast<GoapAgent*>(wagent.second.lock().get());
                agent->update(ms);
            }
        }
    });

    /// kolizje
    addUpdateFunction(1001, [](int ms, EntityManager* entityManager) {
        auto& rbodies = entityManager->get_components()[tindex(CRigidBody)];
        unordered_map<int, weak_ptr<Component>>::iterator c1;
        for(c1 = rbodies.begin(); c1 != rbodies.end(); c1 = std::next(c1)) {
            CRigidBody *rb = static_cast<CRigidBody*>(c1->second.lock().get());
            CMovement *mv = rb->owner.lock()->get<CMovement>();
            CPhysicalForm *pf = rb->owner.lock()->get<CPhysicalForm>();
            if(mv == nullptr || pf == nullptr) continue;

            unordered_map<int, weak_ptr<Component>>::iterator c2;
            for(c2 = next(c1); c2 != rbodies.end(); c2 = std::next(c2)) {
                CRigidBody *rb2 = static_cast<CRigidBody*>(c2->second.lock().get());
                CPhysicalForm *pf2 = rb2->owner.lock()->get<CPhysicalForm>();
                if(pf2 == nullptr) continue;
                if(pf->pos.dist(pf2->pos) < rb->r + rb2->r) { /// kolizja
                    vec3d normal = vec3d(pf->pos.y - pf2->pos.y, pf2->pos.x - pf->pos.x, 0).normalized();
                    mv->speed = normal * mv->speed.len();

                    CMovement *mv2 = rb2->owner.lock()->get<CMovement>();
                    if(mv2 != nullptr) {
                        mv2->speed = -normal * mv2->speed.len();
                    }
                }
            }
        }
    });

    logs::close("done.\n");
    return 0;
}
