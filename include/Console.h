#ifndef CONSOLE_H
#define CONSOLE_H

#include <deque>

#include <SDL.h>

#include "DisplayManager.h"
#include "ScriptSystem.h"

using namespace std;
class Console
{
    public:
        Console(DisplayManager *displayManager, ScriptSystem *scriptSystem);
        virtual ~Console();
        void execute(const string &command);
        void run();
    protected:

    private:
        string buffer;
        deque<string> commandHistory;
        bool _active;
        DisplayManager *_displayManager;
        ScriptSystem *_scriptSystem;
};

#endif // CONSOLE_H
