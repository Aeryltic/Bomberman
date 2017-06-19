#include "Logs.h"

#include <cstdio>
#include <cstdarg>

Logs Logs::instance;

Logs::Logs() : indent(0) {
    //ctor
}

Logs::~Logs() {
    //dtor
}

void Logs::open(std::string format, ...) {
    for(unsigned i=0; i < instance.indent; i++) {
        format = "  " + format;
    }
    va_list args;
    va_start(args, format);
    vprintf(format.c_str(), args);
    va_end(args);
    instance.indent++;
}
void Logs::log(std::string format, ...) {
    for(unsigned i=0; i < instance.indent; i++) {
        format = "  " + format;
    }
    va_list args;
    va_start(args, format);
    vprintf(format.c_str(), args);
    va_end(args);
}
void Logs::close(std::string format, ...) {
    if(instance.indent) instance.indent--;
    for(unsigned i=0; i < instance.indent; i++) {
        format = "  " + format;
    }
    va_list args;
    va_start(args, format);
    vprintf(format.c_str(), args);
    va_end(args);
}
