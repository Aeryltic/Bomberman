#include <exception>

#include "Logs.h"
#include "Engine.h"

int main( int argc, char* args[] ) {
    try {
        Engine::run();
        logs::log("SHUTTING DOWN...\n");
        return 0;
    }
    catch(...){
        logs::log("some exception...\n");
        return -1;
    }
}
