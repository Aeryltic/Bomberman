#ifndef SCRIPT_H
#define SCRIPT_H

#include "Object.h"

class Script
{
    public:
        Script();
        virtual ~Script();
        void run(Object &obj);
    protected:

    private:
        string script;
 //       static ResourceContainer *res;
};

#endif // SCRIPT_H
