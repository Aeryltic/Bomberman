#include "Console.h"
#include <SDL.h>

#include "GameInstance.h"
#include "DisplayManager.h"
#include "ScriptSystem.h"
#include "EventManager.h"
#include "Enumerations.h"

Console::Console(GameInstance *gameInstance)
{
    this->displayManager = gameInstance->getDisplayManager();

    commandHistoryIndex = -1;
    text = new char[1024];
    text[0] = 0;

    visible = false;

    active = true;
}

Console::~Console()
{
    delete [] text;
}

void Console::run()
{
    if (visible)
    {
        displayManager->drawConsole(buffer, history); // to te¿ nie powinno byæ tak
    }
}
void Console::execute(const string &command)
{
    string output = ScriptSystem::instance()->execute(command);
    commandHistory.push_front(command);
    history.push_front(command);
    if(output.length())history.push_front(output);
    printf("executed: %s\n", command.c_str());
}

void Console::init()
{
    EventManager::registerEventCallback(SDL_USEREVENT, [=](SDL_Event const& event)
    {
        switch (event.user.code)
        {
        case EVENT_CONSOLE_TOGGLE:
            toggle();
            EventManager::pushUserEvent(EVENT_PAUSE, nullptr, nullptr);
            break;
        }
    });
    EventManager::registerEventCallback(SDL_TEXTEDITING, [=](SDL_Event const& event)
    {
        if(visible)
        {
            /*
            Update the composition text.
            Update the cursor position.
            Update the selection length (if any).
            */
            printf("EDITING: %s\n", event.edit.text);
            //buffer = string(event.edit.text);
            //composition = event.edit.text;
            //cursor = event.edit.start;
            //selection_len = event.edit.length;
            //buffer = string(text);
        }

    });
    EventManager::registerEventCallback(SDL_TEXTINPUT, [=](SDL_Event const& event)
    {
        if(visible)
        {
            /* Add new text onto the end of our text */
            strcat(text, event.text.text);
            buffer = string(text);
            //printf("INPUT: %s\n", text);
            //execute(string(event.text.text));
        }

    });
    EventManager::registerEventCallback(SDL_KEYDOWN, [=](SDL_Event const& event)
    {
        if(visible)
        {
            SDL_Keycode keycode = event.key.keysym.sym;
            int len = strlen(text);
            switch (keycode)
            {
            case SDLK_RETURN:
                if(len)
                {
                    execute(buffer);
                    text[0] = 0;
                    commandHistoryIndex = -1;
                }
                break;

            case SDLK_BACKSPACE:
                if(len)
                {
                    text[len - 1] = 0;
                }
                break;

            case SDLK_UP:
                if(commandHistoryIndex < int(commandHistory.size()) - 1)
                {
                    commandHistoryIndex++;
                    strcpy(text, commandHistory[commandHistoryIndex].c_str());
                }
                break;

            case SDLK_DOWN:
                if(commandHistoryIndex > 0)
                {
                    commandHistoryIndex--;
                    strcpy(text, commandHistory[commandHistoryIndex].c_str());
                }
            }
            buffer = string(text);
        }
    });
}

void Console::toggle()
{
    visible = !visible;
    if(visible)
    {
        SDL_StartTextInput();
        text[0] = 0;
        commandHistoryIndex = -1;
    }
    else
    {
        SDL_StopTextInput();
    }
    printf("console toggled %s\n", ((visible) ? "ON" : "OFF"));
}
