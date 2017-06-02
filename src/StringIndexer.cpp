#include "StringIndexer.h"

#include <unordered_map>

StringIndexer::StringIndexer() {
    //ctor
}

StringIndexer::~StringIndexer() {
    //dtor
}

unsigned StringIndexer::get_id(std::string& str) {
    static unsigned next_id = 0;
    static std::unordered_map<std::string, unsigned> indexes;

    auto it = indexes.find(str);
    if(it == indexes.end()) {
        indexes[str] = next_id++;
        return indexes[str];
    }
    return it->second;
}
