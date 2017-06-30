#ifndef MISCFUNCTIONS_H_INCLUDED
#define MISCFUNCTIONS_H_INCLUDED

#include "json.hpp"
using json = nlohmann::json;

bool file_to_json(json& j, std::string filename);

#endif // MISCFUNCTIONS_H_INCLUDED
