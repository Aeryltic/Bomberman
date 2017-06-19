#include "MiscFunctions.h"

#include <fstream>
#include <Logs.h>

bool file_to_json(json& j, std::string filename){
    std::ifstream t(filename);
    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    try {
        j = json::parse(str);
    } catch(std::runtime_error& e) {
        logs::log("runtime_error error while loading from %s: %s\n", filename.c_str(), e.what());
        return false;
    } catch(std::invalid_argument& e) {
        logs::log("invalid_argument error while loading from %s: %s\n", filename.c_str(), e.what());
        return false;
    }
    return true;
}
