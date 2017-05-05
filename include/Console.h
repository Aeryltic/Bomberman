#ifndef CONSOLE_H
#define CONSOLE_H

#include <deque>
#include <string>
class GameInstance;
class DisplayManager;
class ScriptSystem;

using namespace std;

class Console
{
    public:
        Console(GameInstance *gameInstance);
        virtual ~Console();
        void execute(const string &command);
        void run();

        void init();
        void toggle();
    protected:

    private:
        string buffer;
        deque<string> commandHistory;
        deque<string> history;
        bool active;
        DisplayManager *displayManager;
        ScriptSystem *scriptSystem;

        int commandHistoryIndex;
        char *text;
        bool visible;
};

#endif // CONSOLE_H
