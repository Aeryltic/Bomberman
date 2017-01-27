#include "DisplayManager.h"
#include <SDL.h>
#include <SDL_image.h>

#include <queue>

DisplayManager::DisplayManager() : _window(WINDOW_WIDTH, WINDOW_HEIGHT)
{
    IMG_Init(IMG_INIT_PNG);
    _graphicsManager = GraphicsManager(_window.getRenderer());
    _windowRect.x = 0;
    _windowRect.y = 0;
    SDL_GetWindowSize(_window._window, &_windowRect.w, &_windowRect.h);
}

DisplayManager::~DisplayManager()
{
    IMG_Quit();
    //dtor
}

void DisplayManager::setup()
{

}
void DisplayManager::render(const ObjectContainer &objects, double interpolation)
{
   // for(auto ins : )
       //Clear screen
    SDL_RenderClear(_window._renderer);
/// TEST
/*
    SDL_Texture *t1 = _graphicsManager.getTexture("textures/player.png");
    SDL_Texture *t2 = _graphicsManager.getTexture("textures/floor.png");
    SDL_Texture *t3 = nullptr;
    SDL_Texture *t4 = nullptr;
    SDL_Texture *t5 = _graphicsManager.getTexture("textures/not_existing.png");
    SDL_Rect a = {.x = 0, .y=0, .w = 128, .h = 128};
    if(t1 == nullptr)
    {
        printf("t1 error\n");
    }
    if(t2 == nullptr)
    {
        printf("t2 error\n");
    }

    SDL_Surface* loadedSurface = IMG_Load( "textures/brick.png" );
    if( loadedSurface == nullptr )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", "textures/brick.png", IMG_GetError() );
//        return -1;
    }
    else
    {
        //Create texture from surface pixels
        t3 = SDL_CreateTextureFromSurface( _window._renderer, loadedSurface );
        SDL_FreeSurface( loadedSurface );
        if( t3 == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", "textures/brick.png", SDL_GetError() );
//            return -1;
        }
    }

    SDL_Texture *tex = nullptr;
    SDL_Surface *s;
    s = SDL_CreateRGBSurface(0, 128, 128, 32, 0, 0, 0, 0);

    SDL_FillRect(s, NULL, SDL_MapRGBA(s->format, 0, 255, 0, 255));
        if(s == nullptr)
        {
            /// error
        }
        else
        {
            tex = SDL_CreateTextureFromSurface(_window._renderer, s);
        }
        SDL_FreeSurface(s);
    t4 = tex;
    if(SDL_RenderCopy( _window._renderer, t1, NULL, &a ))
    {
        printf( "Unable to print texture1! SDL_image Error: %s\n", IMG_GetError() );
    }
    a.x+=128;
    if(SDL_RenderCopy( _window._renderer, t2, NULL, &a ))
    {
        printf( "Unable to print BLANK1! SDL_image Error: %s\n", IMG_GetError() );
    }
    a.x+=128;
    if(SDL_RenderCopy( _window._renderer, t3, NULL, &a ))
    {
        printf( "Unable to print texture2! SDL_image Error: %s\n", IMG_GetError() );
    }
    a.x+=128;
    if(SDL_RenderCopy( _window._renderer, t4, NULL, &a ))
    {
        printf( "Unable to print BLANK2! SDL_image Error: %s\n", IMG_GetError() );
    }
    a.x+=128;
    if(SDL_RenderCopy( _window._renderer, t5, NULL, &a ))
    {
        printf( "Unable to print BLANK3! SDL_image Error: %s\n", IMG_GetError() );
    }
    a.x=0;
    a.y=128;
    if(_graphicsManager.copyTexToRenderer("BLANK",&a))
    {
        printf( "Unable to print BLANK4! SDL_image Error: %s\n", IMG_GetError() );
    }
    SDL_DestroyTexture(t3);
    SDL_DestroyTexture(t4);
    */
/// KONIEC TESTU

    /** tworzy priority_queue
        dla kazdej instancji:
            jesli na ekranie
                oblicza pozycje
                tworzy strukture { SDL_Rect rect, int h}
                wrzuca do kolejki (priorytet po h)
        dla kazdego w kolejce:
            wrzuca do renderera
    */
    priority_queue<ToRender> trt;
    for(auto &o : objects.obj())
    {
        const Object &r = o.second;
        switch (r.type())
        {
            case OBJECT_REAL:
                if(isVisible(r))
                {

                }
                break;
            case OBJECT_BOARD:
                for(int i=0; i<r.height(); i++)
                {
                    for(int j=0; j<r.width(); j++)
                    {
                        Field *field = r.field(i,j);
                    }
                }
                break;
            default:
                break;
        }
    }
    /// SDL_RenderCopyEx - do renderu z obrotem itp
    //Render texture to screen
    //SDL_RenderCopy(_window._renderer, gTexture, NULL, NULL );

    //Update screen
    SDL_RenderPresent(_window._renderer);
}

bool DisplayManager::isVisible(const Object &obj)
{
    /* SDL_bool SDL_IntersectRect(const SDL_Rect* A,
                           const SDL_Rect* B,
                           SDL_Rect*       result)
    */
    SDL_Point p;
    p = obj.lt();
    if(SDL_PointInRect(&p, &_windowRect)) return true;
    p = obj.rt();
    if(SDL_PointInRect(&p, &_windowRect)) return true;
    p = obj.ld();
    if(SDL_PointInRect(&p, &_windowRect)) return true;
    p = obj.rd();
    if(SDL_PointInRect(&p, &_windowRect)) return true;
    return false;
}
