#include "DisplayManager.h"
#include <SDL.h>
#include <SDL_image.h>

#include <queue>
#include "EntityManager.h"
#include "MiscFunctions.h"

DisplayManager::DisplayManager() : _window(WINDOW_WIDTH, WINDOW_HEIGHT), _graphicsManager(GraphicsManager(_window.getRenderer()))
{
    printf("new DisplayManager\n");

    if(IMG_Init(IMG_INIT_PNG) == -1)
    {
        printf("IMG_Init: %s\n", IMG_GetError());
        exit(-1);
    }
    if(TTF_Init() == -1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(-1);
    }

    if(_window.isReady() && _graphicsManager.isActive())
    {
        _windowRect.x = 0;
        _windowRect.y = 0;
        SDL_GetWindowSize(_window.getWindow(), &_windowRect.w, &_windowRect.h);
        printf("_windowRect: %d %d %d %d\n",_windowRect.x,_windowRect.y,_windowRect.w,_windowRect.h);
        _active = true;
    }
    else _active = false;

    consoleFontSize = 30;
    if((consoleFont = TTF_OpenFont("FORCED_SQUARE.ttf", consoleFontSize)) == NULL)
    {
        printf("FONT ERROR\n");
    }
    consoleFontColor = {.r=0, .g=155, .b=0, .a=255};

    clearColor = {.r=0, .g=0, .b=0, .a=255};
    SDL_SetRenderDrawColor(_window.getRenderer(), clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}

DisplayManager::~DisplayManager()
{
    printf("delete DisplayManager\n");

    IMG_Quit();

    TTF_CloseFont(consoleFont);
    consoleFont=NULL;
    TTF_Quit();
}

/*  tworzy priority_queue
    dla kazdej instancji:
        jesli na ekranie
            oblicza pozycje
            tworzy strukture { SDL_Rect rect, int h}
            wrzuca do kolejki (priorytet po h)
    dla kazdego w kolejce:
        wrzuca do renderera
*/
void DisplayManager::render(const EntityManager *entityManager, int ms)
{
    SDL_RenderClear(_window.getRenderer());
    priority_queue<ToRender> trt;
    for(auto &entity_m : entityManager->entity())
    {
        entity_ptr entity = entity_m.second;
        if(entity->has<PhysicalForm>() && entity->has<TextureComponent>())
        {
            SDL_Rect rect = entity->get<PhysicalForm>()->rect(ms);
            if(isVisible(rect))
            {
                SDL_Texture *texture = entity->get<TextureComponent>()->texture(); /// animacje!
                int z = entity->get<PhysicalForm>()->getZ();
                double angle = entity->get<PhysicalForm>()->getAngle();
                trt.push(ToRender(texture, rect, z, angle));
            }
        }
    }
    while(!trt.empty())
    {
        auto &sth = trt.top();
        if(SDL_RenderCopyEx(_window.getRenderer(), sth.texture, NULL, &sth.rect, degrees(sth.angle), NULL, SDL_FLIP_NONE) < 0)
        {
            printf("SDL_RenderCopy - Error\n");
        }
        trt.pop();
    }
    showDialog("abcdefghijklmnoprstuvwxyz");
    SDL_RenderPresent(_window.getRenderer());
}

bool DisplayManager::isVisible(const SDL_Rect &rect) /// ta funckja powinna uwzgledniaæ obrot, bo tak obiekty na skraju moga sie nie pojawic mimo ze powinny
{
    SDL_Point p;
    p.x = rect.x;
    p.y = rect.y;
    if(SDL_PointInRect(&p, &_windowRect)) return true;
    p.x += rect.w;
    if(SDL_PointInRect(&p, &_windowRect)) return true;
    p.y += rect.h;
    if(SDL_PointInRect(&p, &_windowRect)) return true;
    p.x -= rect.w;
    if(SDL_PointInRect(&p, &_windowRect)) return true;
    return false;
}
void DisplayManager::showDialog(const string &text)
{
    int len = text.length();

    SDL_Rect textRect;
    textRect.w = consoleFontSize * len + 50;
    textRect.h = consoleFontSize + 50;
    textRect.x = (_windowRect.w - textRect.w) / 2;
    textRect.y = (_windowRect.h - textRect.h) / 2;
    SDL_Color boxColor = {.r=50, .g=50, .b=50, .a=255};

    drawRectangle(textRect, boxColor);
    drawText(text, consoleFontColor);
}
void DisplayManager::drawRectangle(const SDL_Rect &rect, const SDL_Color &color)
{
    SDL_SetRenderDrawColor(_window.getRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(_window.getRenderer(), &rect);
    SDL_SetRenderDrawColor(_window.getRenderer(), clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}
void DisplayManager::drawText(const string &text, const SDL_Color &color)
{
    int len = text.length();

    SDL_SetRenderDrawColor(_window.getRenderer(), color.r, color.g, color.b, color.a);

    SDL_Surface* messageSurface = TTF_RenderText_Solid(consoleFont, text.c_str(), consoleFontColor);
    SDL_Texture* message = SDL_CreateTextureFromSurface(_window.getRenderer(), messageSurface);
    SDL_FreeSurface(messageSurface);

    SDL_Rect textRect;
    TTF_SizeText(consoleFont, text.c_str(), &textRect.w, &textRect.h);
    textRect.x = (_windowRect.w - textRect.w) / 2;
    textRect.y = (_windowRect.h - textRect.h) / 2;

    SDL_RenderCopy(_window.getRenderer(), message, NULL, &textRect);

    SDL_SetRenderDrawColor(_window.getRenderer(), clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}
