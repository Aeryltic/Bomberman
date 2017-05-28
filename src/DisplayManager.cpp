#include "DisplayManager.h"
#include <SDL.h>
#include <SDL_image.h>

#include <queue>
#include "GameInstance.h"
#include "EntityManager.h"

#include "ScriptSystem.h"
#include "Components.h"


#include "SDL2_gfxPrimitives.h"



DisplayManager::DisplayManager(GameInstance *gameInstance) : _window(WINDOW_WIDTH, WINDOW_HEIGHT)//, _graphicsManager(GraphicsManager(_window.getRenderer()))
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

    if(_window.isReady())
    {
        _windowRect.x = 0;
        _windowRect.y = 0;
        SDL_GetWindowSize(_window.getWindow(), &_windowRect.w, &_windowRect.h);
        printf("_windowRect: %d %d %d %d\n",_windowRect.x,_windowRect.y,_windowRect.w,_windowRect.h);
        _active = true;
    }
    else _active = false;

    consoleFontSize = 20;
    if((consoleFont = TTF_OpenFont("fonts/FORCED_SQUARE.ttf", consoleFontSize)) == NULL)
    {
        printf("FONT ERROR\n");
    }
    consoleFontColor = {.r=0, .g=155, .b=0, .a=255};

    clearColor = {.r=0, .g=0, .b=0, .a=255};
    SDL_SetRenderDrawColor(_window.getRenderer(), clearColor.r, clearColor.g, clearColor.b, clearColor.a);

    _gameWorldView = SDL_CreateTexture(_window.getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _windowRect.w, _windowRect.h);
}

DisplayManager::~DisplayManager()
{
    printf("delete DisplayManager\n");

    SDL_DestroyTexture(_gameWorldView);

    IMG_Quit();

    TTF_CloseFont(consoleFont);
    consoleFont=NULL;
    TTF_Quit();
}

/*  render():
        tworzy priority_queue
        dla kazdej instancji:
            jesli na ekranie
                oblicza pozycje
                tworzy strukture {SDL_Rect rect, int h}
                wrzuca do kolejki (priorytet po h)
        dla kazdego w kolejce:
            renderuje
*/

void DisplayManager::render(EntityManager *entityManager, int ms)
{
    //printf("ms: %d\n", ms);
    if(!GameInstance::isPaused())
    {
        // renderowanie
        SDL_SetRenderTarget(_window.getRenderer(), _gameWorldView);
        SDL_RenderClear(_window.getRenderer());

        //priority_queue<ToRender> trt;
        for(auto &component : entityManager->getComponents()[tindex(CAspect)])
        {
            CAspect *asp = static_cast<CAspect*>(component.lock().get());
            CPhysicalForm *pf = static_cast<CPhysicalForm*>(component.lock()->owner.lock()->get<CPhysicalForm>());
            float r = pf->vol.x / 2;

            SDL_Rect rect{.x = (int)pf->pos.x, .y = (int)pf->pos.y, .w = (int)pf->vol.x, .h = (int)pf->vol.y};

//            CMovement *m = component.lock()->owner.lock()->get<CMovement>(); /// "piękne"
//            if(m != nullptr)
//            {
//                rect.x += m->speed.x * ms / 1000.0;
//                rect.y += m->speed.y * ms / 1000.0;
//            }
            //drawRectangle(rect, SDL_Color{.r=255,.g=0,.b=0,.a=255});
            filledCircleRGBA (_window.getRenderer(), rect.x, rect.y, r, asp->color.r, asp->color.g, asp->color.b, asp->color.a);
        }


        /*
                while(!trt.empty())
                {
                    auto &sth = trt.top();
                    if(SDL_RenderCopyEx(_window.getRenderer(), sth.texture, NULL, &sth.rect, degrees(sth.angle), NULL, SDL_FLIP_NONE) < 0)
                    {
                        printf("SDL_RenderCopy - Error\n");
                    }
                    trt.pop();
                }
        */
        showDialog(text, POS_RIGHT_TOP); /// TEST

        SDL_SetRenderTarget(_window.getRenderer(), nullptr); // przywracam właściwy renderer

        SDL_RenderClear(_window.getRenderer());
        SDL_RenderCopy(_window.getRenderer(), _gameWorldView, nullptr, nullptr);
        SDL_RenderPresent(_window.getRenderer());
    }
}

void DisplayManager::drawConsole(const string &buffer, const deque<string> &commandHistory)
{
    SDL_RenderClear(_window.getRenderer());

    SDL_RenderCopy(_window.getRenderer(), _gameWorldView, nullptr, nullptr);

    SDL_Color consoleColor = {.r=50, .g=50, .b=50, .a=255};
    SDL_Rect consoleRect = {.x=0, .y=_windowRect.h - 7*(consoleFontSize+2), .w=_windowRect.w, .h=7*(consoleFontSize+2)};
    drawRectangle(consoleRect, consoleColor);

    string formatted_buffer = ">> " + buffer;
    int x0 = 20;
    int y0 = _windowRect.h - consoleFontSize*2;
    drawText(formatted_buffer, x0, y0, consoleFontColor);
    for(unsigned i=0; (i<5) && (i<commandHistory.size()); i++)
    {
        drawText(commandHistory[i], x0, y0 - (i+1)*consoleFontSize, consoleFontColor);
    }

    SDL_RenderPresent(_window.getRenderer());
}

bool DisplayManager::isVisible(const SDL_Rect &rect) /// ta funkcja powinna uwzgledniać obrot, bo tak obiekty na skraju moga sie nie pojawic mimo ze powinny
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

void DisplayManager::showDialog(const string &text, BoxPosition position)
{
    //printf("dialog with: \"%s\"\n", text.c_str());
    int textW, textH;
    TTF_SizeText(consoleFont, text.c_str(), &textW, &textH);

    SDL_Rect textRect;
    textRect.w = textW + 50;
    textRect.h = textH + 50;

    switch (position)
    {
    case POS_CENTER:
        textRect.x = (_windowRect.w - textRect.w) / 2;
        textRect.y = (_windowRect.h - textRect.h) / 2;
        break;

    case POS_LEFT:
        textRect.x = 0;
        textRect.y = (_windowRect.h - textRect.h) / 2;
        break;
    case POS_RIGHT:
        textRect.x = _windowRect.w - textRect.w;
        textRect.y = (_windowRect.h - textRect.h) / 2;
        break;
    case POS_TOP:
        textRect.x = (_windowRect.w - textRect.w) / 2;
        textRect.y = 0;
        break;
    case POS_BOTTOM:
        textRect.x = (_windowRect.w - textRect.w) / 2;
        textRect.y = (_windowRect.h - textRect.h);
        break;

    case POS_LEFT_TOP:
        textRect.x = 0;
        textRect.y = 0;
        break;
    case POS_RIGHT_TOP:
        textRect.x = _windowRect.w - textRect.w;
        textRect.y = 0;
        break;
    case POS_LEFT_BOTTOM:
        textRect.x = 0;
        textRect.y = (_windowRect.h - textRect.h);
        break;
    case POS_RIGHT_BOTTOM:
        textRect.x = _windowRect.w - textRect.w;
        textRect.y = (_windowRect.h - textRect.h);
        break;
    default:
        textRect.x = 0;
        textRect.y = 0;
        break;
    }

    SDL_Color boxColor = {.r=50, .g=50, .b=50, .a=255};

    drawRectangle(textRect, boxColor);
    drawText(text, textRect.x + 25, textRect.y + 25, consoleFontColor);
}

void DisplayManager::drawRectangle(const SDL_Rect &rect, const SDL_Color &color)
{
    SDL_SetRenderDrawColor(_window.getRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(_window.getRenderer(), &rect);
    SDL_SetRenderDrawColor(_window.getRenderer(), clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}

void DisplayManager::drawText(const string &text, int x, int y, const SDL_Color &color)
{
    SDL_SetRenderDrawColor(_window.getRenderer(), color.r, color.g, color.b, color.a);

    SDL_Surface* messageSurface = TTF_RenderText_Solid(consoleFont, text.c_str(), consoleFontColor);
    SDL_Texture* message = SDL_CreateTextureFromSurface(_window.getRenderer(), messageSurface);
    SDL_FreeSurface(messageSurface);

    SDL_Rect textRect;
    TTF_SizeText(consoleFont, text.c_str(), &textRect.w, &textRect.h);
    textRect.x = x;
    textRect.y = y;

    SDL_RenderCopy(_window.getRenderer(), message, NULL, &textRect);
    SDL_DestroyTexture(message);

    SDL_SetRenderDrawColor(_window.getRenderer(), clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}

void DisplayManager::init()
{
    lua_State *L = ScriptSystem::getInstance()->getLuaState();

    getGlobalNamespace (L)
    .beginClass <DisplayManager> ("DisplayManager")
    .addProperty ("text", &DisplayManager::getText, &DisplayManager::setText)
    .endClass();

    push (L, this);
    lua_setglobal (L, "display");
}

