#include "Component.h"

#include "EntityManager.h"

EntityManager* Component::entity_manager = nullptr;

Component::~Component() { }

void Component::set_manager(EntityManager* entity_manager) {
    Component::entity_manager = entity_manager;
}

void Component::set_owner(std::weak_ptr<Entity> owner) {
    /// ten setter mu być
    this->owner = owner;
}
