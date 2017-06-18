#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <memory>
#include <unordered_map>

#include "json.hpp"

using json = nlohmann::json;

class Entity;
class EntityManager;
class Component;

class ObjectSchema {
public:
    void add_component(std::string cname, json j_obj) {
        components.push_back(make_pair(cname, j_obj));
    }
    std::vector<std::pair<std::string, json>>& get_components(){return components;}
private:
    std::vector<std::pair<std::string, json>> components;
};

class ObjectFactory {
    using entity_creator = std::function<std::shared_ptr<Entity>(double, double)>;
    using component_creator = std::function<std::shared_ptr<Component>(json j_obj)>;

public:
    ObjectFactory(EntityManager* entityManager);
    virtual ~ObjectFactory();
    std::shared_ptr<Entity> make_object(std::string type, double x, double y);

private:
    std::unordered_map<std::string, component_creator> components;
    //std::unordered_map<unsigned, entity_creator> constructors;
    std::unordered_map<std::string, ObjectSchema> object_schemas;

    EntityManager* entityManager;

    void init_component_constructors();
    void init_entity_constructors();
};
#endif // OBJECTFACTORY_H
