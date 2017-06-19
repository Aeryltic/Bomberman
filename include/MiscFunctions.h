#ifndef MISCFUNCTIONS_H_INCLUDED
#define MISCFUNCTIONS_H_INCLUDED

#include <typeindex>
#include <typeinfo>

#include "json.hpp"
using json = nlohmann::json;

/// BOSKIE MAKRO
#define tindex(a) type_index(typeid(a))

bool file_to_json(json& j, std::string filename);

#endif // MISCFUNCTIONS_H_INCLUDED
