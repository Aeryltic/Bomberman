#include "ComponentSystem.h"

#include "EntityManager.h"
#include "Views.h"

void ComponentSystem::update(int timestep, EntityManager *entityManager)
{
    for(auto &p : ufunctions)
    {
        p.second(timestep, entityManager);
    }
}

void ComponentSystem::addUpdateFunction(int priority, update_function ufunction)
{
    ufunctions.push_back(make_pair(priority, ufunction));
}

bool ComponentSystem::init()
{
    /// jakiś tam ruch
    addUpdateFunction(10, [](int ms, EntityManager* entityManager) /// tylko test
    {
        vector<MovementView> views = ViewCreator::createViews<MovementView>(entityManager);
        for(auto &v: views)
        {
            if(v.m->has_dest == false)
            {
                if(SDL_GetTicks() > v.m->wait_end)  // to jest w ogóle bardzo brzydkie bo zależy od ilości updatów na sekundę
                {
//                    float angle = (rand()%360) * M_PI / 180.0;
//                    float dx = 100 * cos(angle),
//                            dy = 100 * sin(angle);
//                    v.m->dest = vec3d(v.pf->pos.x + dx, v.pf->pos.y + dy, v.pf->pos.z);
                    auto p = random_point_in_range(v.pf->pos.x, v.pf->pos.y, 100, 200);
                    p.z = v.pf->pos.z;
                    v.m->dest = p;
                    v.m->has_dest = true;
                }
            }
            else
            {
                v.pf->pos += v.m->speed;

                if(v.m->dest.dist(v.pf->pos) < 10)
                {
                    v.m->has_dest = false;
                    v.m->speed.x = 0;
                    v.m->speed.y = 0;
                    v.m->speed.z = 0;

                    v.m->wait_end = SDL_GetTicks() + 100 + rand()%1500;
                }
                else // aktualizacja prędkości jakby się coś zmieniło
                {
                    float angle = atan2(v.m->dest.y - v.pf->pos.y, v.m->dest.x - v.pf->pos.x);
                    v.m->speed.x = v.m->max_speed * cos(angle) * ms / 1000;
                    v.m->speed.y = v.m->max_speed * sin(angle) * ms / 1000;
                }
            }
        }
    });
    /// breedery

    addUpdateFunction(20, [](int ms, EntityManager* entityManager)
    {
        vector<BreederView> views = ViewCreator::createViews<BreederView>(entityManager);
        for(auto &view: views)
        {
            if(view.breeder->ready())
            {
                view.energy->amount -= view.breeder->required_energy;
                int amount = rand()%(view.breeder->max_amount - view.breeder->min_amount) + view.breeder->min_amount;
                while(amount--)
                {
                    vec3d p = random_point_in_range(view.pf->pos.x, view.pf->pos.y, view.pf->vol.x, view.pf->vol.x*2);
                    entityManager->make_object(view.breeder->child_type, p.x, p.y);
                }
            }
        }
    });

    /// odnawianie energii
    addUpdateFunction(20, [](int ms, EntityManager* entityManager)
    {
        vector<EnergyView> views = ViewCreator::createViews<EnergyView>(entityManager);
        for(auto &view: views)
        {
            view.energy->amount += view.energy->pace * ms / 1000.0;
        }
    });

    return 0;
}
