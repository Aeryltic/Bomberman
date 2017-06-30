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
    format = ">" + format;
    for(unsigned i=0; i < instance.indent; i++) {
        format = "| " + format;
    }
    va_list args;
    va_start(args, format);
    vprintf(format.c_str(), args);
    va_end(args);
    instance.indent++;
}

void Logs::log(std::string format, ...) {
    //format = " " + format;
    for(unsigned i=0; i < instance.indent; i++) {
        format = "| " + format;
    }
    va_list args;
    va_start(args, format);
    vprintf(format.c_str(), args);
    va_end(args);
}

void Logs::close(std::string format, ...) {
    format = "^" + format;
    if(instance.indent) instance.indent--;
    for(unsigned i=0; i < instance.indent; i++) {
        format = "| " + format;
    }
    va_list args;
    va_start(args, format);
    vprintf(format.c_str(), args);
    va_end(args);
}

void Logs::sopen(std::string text){
    open((text+'\n').c_str());
}

void Logs::slog(std::string text){
    log((text+'\n').c_str());
}

void Logs::sclose(std::string text){
    close((text+'\n').c_str());
}
