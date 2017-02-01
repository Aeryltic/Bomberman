#include "DisplayManager.h"
#include <SDL.h>
#include <SDL_image.h>

#include <queue>
#include "EntityManager.h"
#include "MiscFunctions.h"

DisplayManager::DisplayManager() : _window(WINDOW_WIDTH, WINDOW_HEIGHT)
{
    printf("new DisplayManager\n");
    IMG_Init(IMG_INIT_PNG);
    _graphicsManager = GraphicsManager(_window.getRenderer());//make_shared<GraphicsManager>(_window.getRenderer());
    //_graphicsManager = GraphicsManager(_window.getRenderer());
    _windowRect.x = 0;
    _windowRect.y = 0;
    SDL_GetWindowSize(_window.getWindow(), &_windowRect.w, &_windowRect.h);
    printf("_windowRect: %d %d %d %d\n",_windowRect.x,_windowRect.y,_windowRect.w,_windowRect.h);
}

DisplayManager::~DisplayManager()
{
    printf("delete DisplayManager\n");
    IMG_Quit();
    //dtor
}

void DisplayManager::setup()
{

}

void DisplayManager::render(const EntityManager *entityManager, int ms) /// wlasciwie to jest prawie gotowa tylko testowac
{

    SDL_RenderClear(_window.getRenderer());
  //  _graphicsManager.test(_window);
   // test();
    /*  tworzy priority_queue
        dla kazdej instancji:
            jesli na ekranie
                oblicza pozycje
                tworzy strukture { SDL_Rect rect, int h}
                wrzuca do kolejki (priorytet po h)
        dla kazdego w kolejce:
            wrzuca do renderera
    */
    priority_queue<ToRender> trt;
    for(auto &entity_m : entityManager->entity())
    {
        entity_ptr entity = entity_m.second;
        //if(entity->isActive())
        {
            if(entity->hasComponent<PhysicalFormComponent>() && entity->hasComponent<TextureComponent>())
            {
                SDL_Rect rect = entity->getComponent<PhysicalFormComponent>()->rect(ms);
                //printf("rect: %d %d %d %d\n",rect.x, rect.y, rect.w, rect.h);
                if(isVisible(rect))
                {
                    SDL_Texture *texture = entity->getComponent<TextureComponent>()->texture();
                    int z = entity->getComponent<PhysicalFormComponent>()->getZ();
                    double angle = entity->getComponent<PhysicalFormComponent>()->getAngle();
                    trt.push(ToRender(texture, rect, z, angle));
                }
            }
        }
    }
    //printf("rendering: %d\n",trt.size());
    while(!trt.empty())
    {
        auto &sth = trt.top();
        //if(sth.texture == nullptr) printf("nullptr texture - how?\n");
        if(SDL_RenderCopyEx(_window.getRenderer(), sth.texture, NULL, &sth.rect, degrees(sth.angle), NULL, SDL_FLIP_NONE) < 0)
        {
            printf("SDL_RenderCopy - Error\n");
        }
        trt.pop();
    }
    /// SDL_RenderCopyEx - do renderu z obrotem itp

    SDL_RenderPresent(_window.getRenderer());
}

bool DisplayManager::isVisible(const SDL_Rect &rect) /// ta funckja powinna uwzgledniach obrot, bo tak obiekty na skraju moga sie niepojawic mimo ze powinny
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

void DisplayManager::test()
{
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
        t3 = SDL_CreateTextureFromSurface( _window.getRenderer(), loadedSurface );
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
            tex = SDL_CreateTextureFromSurface(_window.getRenderer(), s);
        }
        SDL_FreeSurface(s);
    t4 = tex;
    if(SDL_RenderCopy( _window.getRenderer(), t1, NULL, &a ))
    {
        printf( "Unable to print texture1! SDL_image Error: %s\n", IMG_GetError() );
    }
    a.x+=128;
    if(SDL_RenderCopy( _window.getRenderer(), t2, NULL, &a ))
    {
        printf( "Unable to print BLANK1! SDL_image Error: %s\n", IMG_GetError() );
    }
    a.x+=128;
    if(SDL_RenderCopy( _window.getRenderer(), t3, NULL, &a ))
    {
        printf( "Unable to print texture2! SDL_image Error: %s\n", IMG_GetError() );
    }
    a.x+=128;
    if(SDL_RenderCopy( _window.getRenderer(), t4, NULL, &a ))
    {
        printf( "Unable to print BLANK2! SDL_image Error: %s\n", IMG_GetError() );
    }
    a.x+=128;
    if(SDL_RenderCopy( _window.getRenderer(), t5, NULL, &a ))
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
}
