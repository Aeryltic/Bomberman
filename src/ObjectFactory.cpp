#include "ObjectFactory.h"

#include <fstream>

#include "Entity.h"
#include "EntityManager.h"
#include "Components.h"
#include "GoapAgent.h"

#include "StringIndexer.h"

#include "AIPackage.h"


ObjectFactory::ObjectFactory(EntityManager* entityManager) : entityManager(entityManager) { /// to ma wylądować w skryptach
    Action::init_actions();
    Action::init_action_packs();

    init_component_constructors();
    init_entity_constructors();
}

void ObjectFactory::init_component_constructors() {
    components["CPhysicalForm"] = ([=](json j_obj) {
        return entityManager->make_component<CPhysicalForm>(0, 0, 0, j_obj[3], j_obj[4]); /// to jest problematyczne
    });
    components["CAspect"] = ([=](json j_obj) {
        return entityManager->make_component<CAspect>(j_obj[0], j_obj[1], j_obj[2], j_obj[3]);
    });
    components["CMovement"] = ([=](json j_obj) {
        return entityManager->make_component<CMovement>(j_obj[0].get<double>());
    });
    components["CActionTarget"] = ([=](json j_obj) {
        return entityManager->make_component<CActionTarget>(j_obj[0].get<string>());
    });
    components["CEnergyStore"] = ([=](json j_obj) {
        return entityManager->make_component<CEnergyStore>(j_obj[0].get<double>());
    });
    components["CBreeder"] = ([=](json j_obj) {
        return entityManager->make_component<CBreeder>(j_obj[0], j_obj[1], j_obj[2], j_obj[3]);
    });
    components["CNeeds"] = ([=](json j_obj) {
        return entityManager->make_component<CNeeds>(j_obj[0], j_obj[1], j_obj[2]);
    });
    components["CRigidBody"] = ([=](json j_obj) {
        return entityManager->make_component<CRigidBody>(j_obj[0].get<double>());
    });
    components["GoapAgent"] = ([=](json j_obj) { /// wiem, dużo kopiowania - to się potem zmieni, ale nie chce mi się wymyślać wszystkiego na nowo. drobnymi kroczkami...
        std::shared_ptr<Component> c = entityManager->make_component<GoapAgent>();
        GoapAgent* agent = static_cast<GoapAgent*>(c.get());
        for(string pack_name: j_obj) {
            const AIPackage& ai_pack = Action::get_ai_package(pack_name);
            for(const string& action_name: ai_pack.get_actions()) {
                agent->add_action(Action::get_action(action_name));
            }
            for(const auto& p: ai_pack.get_goals()) {
                agent->add_goal(p.second.first, p.second.second, p.first);
            }
        }
        return c;
    });
    components["CAbstractObjectContainer"] = ([=](json j_obj) {
        return entityManager->make_component<CAbstractObjectContainer>();
    });
}

void ObjectFactory::init_entity_constructors() {
    printf("initializing object schemas...\n");
    std::string filename("data/objects.json");
    std::ifstream t(filename);
    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    json j;
    str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    try {
        j = json::parse(str);
    } catch(runtime_error& e) {
        printf("runtime_error error while loading from %s: %s\n", filename.c_str(), e.what());
        return;
    } catch(invalid_argument& e) {
        printf("invalid_argument error while loading from %s: %s\n", filename.c_str(), e.what());
        return;
    }

    for(auto p : j) {
        try {
            std::string schema_name = p["name"];
            printf("\tnew schema: %s!\n", schema_name.c_str());
            ObjectSchema os;
            for(auto c: p["components"]) {
                try {
                    os.add_component(c[0], c[1]);
                } catch(domain_error& e) {
                    printf("bad component table: %s (%s)\n", e.what(), c.get<std::string>().c_str());
                }
            }
            object_schemas.insert({(schema_name), std::move(os)});
        } catch(invalid_argument& e) {
            printf("error while loading from %s: %s\n", filename.c_str(), e.what());
        } catch(domain_error& e) {
            printf("bad package: %s (%s)\n", e.what(), p.get<std::string>().c_str());
        }
    }
    printf("schemas initialized!\n");
}

ObjectFactory::~ObjectFactory() {
    //dtor
}

shared_ptr<Entity> ObjectFactory::make_object(std::string type, double x, double y) {
    shared_ptr<Entity> e = nullptr;
    if(object_schemas.find(type) != object_schemas.end()) {
        //e = constructors[type](x, y);
        e = entityManager->make_entity();

        for(const auto& p: object_schemas[type].get_components()) {
            try {
                e->add(components[p.first](p.second));
                //printf("\t'%s' added\n", p.first.c_str());
            } catch(bad_function_call& e) {
                printf("%s (tried to call component[%s](%s))\n", e.what(), p.first.c_str(), p.second.dump().c_str());
            }
        }
        CPhysicalForm* pf = e->get<CPhysicalForm>();
        if(pf) {
            pf->pos = {x, y, 0};
        } else {
            printf("object has no PhysicalForm\n");
        }
        //printf("new %s (#%d) at (%f,%f)\n", type.c_str(), e->get_id(), x, y);
    } else {
        printf("unknown object type: \"%s\".\n", type.c_str());
    }
    return e;
}
