#include "InputManager.h"
#include <cstdio>
InputManager::InputManager()
{
    printf("new InputManager\n");
}

InputManager::~InputManager()
{
    printf("delete InputManager\n");
}
void InputManager::update()
{
    for(auto &key : _key)
    {
        //if((key.second)&(KEY_PRESSED|KEY_RELEASED))key.second<<=1; /// doesn't work with enums
        if(key.second == KEY_PRESSED) key.second = KEY_DOWN;//, printf("down: %s\n",SDL_GetKeyName(key.first));
        else if(key.second == KEY_RELEASED) key.second = KEY_UP;//, printf("up: %s\n",SDL_GetKeyName(key.first));
    }
}

void InputManager::setKeyStatus(SDL_Keycode keycode, KeyStatus status)
{
    //if(!((_key[keycode]>>1) & status))_key[keycode] = status; /// doesn't work with enums
    if((status == KEY_PRESSED) && (_key[keycode] != KEY_DOWN)) _key[keycode] = KEY_PRESSED;
    else if(status == KEY_RELEASED) _key[keycode] = KEY_RELEASED;
}
