#include "Console.h"

Console::Console(DisplayManager *displayManager, ScriptSystem *scriptSystem)
{
    _displayManager = displayManager;
    _scriptSystem = scriptSystem;
}

Console::~Console()
{
    //dtor
}
void Console::run()
{
    SDL_StartTextInput();

    char *text = new char[1024];
    text[0] = 0;
    int commandHistoryIndex = -1;
    bool done = false;
    while (!done)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_TEXTEDITING:
                    /*
                    Update the composition text.
                    Update the cursor position.
                    Update the selection length (if any).
                    */
                    //printf("EDITING: %s\n", event.edit.text);
//                    buffer = string(event.edit.text);
//                    composition = event.edit.text;
//                    cursor = event.edit.start;
//                    selection_len = event.edit.length;
                    break;
                case SDL_TEXTINPUT:
                    /* Add new text onto the end of our text */
                    strcat(text, event.text.text);
                    buffer = string(text);
                    //printf("INPUT: %s\n", text);
                    //execute(string(event.text.text));
                    break;
                case SDL_KEYDOWN:
                    SDL_Keycode keycode = event.key.keysym.sym;
                    int len = strlen(text);
                    switch (keycode)
                    {
                        case SDLK_ESCAPE:
                            done = true;
                            break;

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
                    break;
            }
        }
        _displayManager->drawConsole(buffer, commandHistory);
    }
    SDL_StopTextInput();
}
void Console::execute(const string &command)
{
    _scriptSystem->execute(command);
    commandHistory.push_front(command);
    printf("executed: %s\n", command.c_str());
}
