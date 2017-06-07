#include "Component.h"

#include "EntityManager.h"

EntityManager* Component::entity_manager = nullptr;
int Component::nextID = 0;

Component::Component() : id(nextID++) {}
Component::~Component() { }

void Component::set_manager(EntityManager* entity_manager) {
    Component::entity_manager = entity_manager;
}

void Component::set_owner(std::weak_ptr<Entity> owner) {
    /// ten setter musi być
    this->owner = owner;
}
