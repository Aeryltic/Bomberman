#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "AppWindow.h"
//#include "GraphicsManager.h"

#include <memory>
#include <SDL.h>
#include "SDL_ttf.h"

#include <deque>

#include "Enumerations.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

class EntityManager;
//class ObjectContainer;

using namespace std;

class GameInstance;

class DisplayManager
{
    /// -----------------------------------
    struct ToRender
    {
        ToRender(SDL_Texture *texture, const SDL_Rect &rect, int z, double angle = 0) : texture(texture), rect(rect), z(z), angle(angle) {}

        SDL_Texture *texture;
        SDL_Rect rect;
        int z;
        double angle;

        friend bool operator<(const ToRender &a, const ToRender &b)
        {
            return a.z > b.z;
        }
    };
    /// -----------------------------------
public:
    DisplayManager(GameInstance *gameInstance); /// pic na wodę, fotomontaż
    virtual ~DisplayManager();

    void drawConsole(const string &buffer, const deque<string> &commandHistory);
    //void render(EntityManager *entityManager, int ms);
    void render(EntityManager *entityManager, double interpolation);

    bool isVisible(const SDL_Rect &rect);

//        GraphicsManager *getGraphicsManager(){return &_graphicsManager;}
    bool isActive()
    {
        if(!_active)printf("DisplayManager is not active\n");
        return _active;
    }

    void showDialog(const string &text, BoxPosition position = POS_CENTER);
    void drawRectangle(const SDL_Rect &rect, const SDL_Color &color);
    void drawText(const string &text, int x, int y, const SDL_Color &color);

    /// TESTY
    string text;
    void setText(const std::string& test)
    {
        text = test;
    }
    string getText() const
    {
        return text;
    }

    void init();
    /// -----------
protected:

private:
    bool _active;
    AppWindow _window;
//        GraphicsManager _graphicsManager;
    SDL_Rect _windowRect;

    SDL_Texture *_gameWorldView;

    TTF_Font* consoleFont;
    int consoleFontSize;
    SDL_Color consoleFontColor;

    SDL_Color clearColor;
    SDL_Texture *gameViewBuffer;
};

#endif // DISPLAYMANAGER_H
