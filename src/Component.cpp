#include "Component.h"

#include "EntityManager.h"

EntityManager* Component::entity_manager = nullptr;

Component::~Component() {
    //printf("del comp...");
    if(entity_manager) {
            //printf(" ok...");
        entity_manager->request_component_removal(tindex(*this), id);
    }
    //printf("\n");
}

void Component::set_manager(EntityManager* entity_manager) {
    Component::entity_manager = entity_manager;
}
