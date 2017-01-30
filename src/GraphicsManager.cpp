#include "GraphicsManager.h"
#include <fstream>
GraphicsManager::GraphicsManager()
{
    printf("new GraphicsManager\n");
    _renderer = nullptr;
}
GraphicsManager::GraphicsManager(SDL_Renderer *renderer)
{
    printf("new GraphicsManager\n");
    _renderer = renderer;
    createBlankTexture();
    //ctor
}

GraphicsManager::~GraphicsManager()
{
    printf("delete GraphicsManager\n");
    for(auto &tex : textures)
        SDL_DestroyTexture(tex.second);
    textures.clear();
}
SDL_Texture *GraphicsManager::getTexture(const string &path) ///nie powinien ladowac
{
    /** uzywana przy ladowaniu obiektow. sprawdza czy juz jest, jesli nie ma probuje zaladowac, jesli nie moze - BLANK */
    SDL_Texture *texture;
    texture = 0;
    unordered_map<string,SDL_Texture*>::iterator found = textures.find(path);
    if(found == textures.end())
    {
        printf("Texture: %s not found. Loading texture.\n", path.c_str());
        loadTexture(path);
    }
    texture = textures[path];
    if(texture == nullptr) texture = textures["BLANK"]; // if doesnt exist

    return texture;//->SDL_Tex();
}

SDL_Texture *GraphicsManager::getTexture(const char *path)
{
    string tmp(path);
    return getTexture(tmp);
}

int GraphicsManager::copyTexToRenderer(const char *tex, SDL_Rect *rect)
{
    return SDL_RenderCopy(_renderer, textures[tex], NULL, rect);
}
/*
int GraphicsManager::loadTextures(const char *reference_file_path) // NIE DZIALA JESZCZE WCALE
{
    // to nie bedzie tak dzialac, przebudowac do ladowania konkretnej tekstury, albo jeszcze inaczej
    createBlankTexture();

    ifstream tex_stream;
    tex_stream.open(reference_file_path);
    if(tex_stream.is_open())
    {
        string word;
        while(tex_stream>>word)
        {
            if(word == "<")
            {
                string name;
            }
        }
    }
    else return -1;
    return 0;
}
*/
bool GraphicsManager::loadTexture(string texture_path) /// uproscic to bo okropnie wyglada
{
    if(textures.find(texture_path) == textures.end())
    {
        printf("Loading texture: %s\n",texture_path.c_str());
        SDL_Texture* newTexture = NULL;

        SDL_Surface* loadedSurface = IMG_Load(texture_path.c_str());
        if(loadedSurface == nullptr)
        {
            printf("Unable to load image %s! SDL_image Error: %s\n", texture_path.c_str(), IMG_GetError());
            textures.insert(make_pair(texture_path,nullptr));
            return 0;
        }
        else
        {
            newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
            SDL_FreeSurface(loadedSurface);
            if(newTexture == NULL)
            {
                printf("Unable to create texture from %s! SDL Error: %s\n", texture_path.c_str(), SDL_GetError());
                textures.insert(make_pair(texture_path,nullptr));
                return 0;
            }
        }
        textures.insert(make_pair(texture_path,newTexture));
        printf("Texture loaded.\n");
        return 1;
    }
    else
    {
        printf("Can't load %s - already exists.\n",texture_path.c_str());
        return 0;
    }
}

void GraphicsManager::createBlankTexture()
{
    if(textures.find("BLANK") == textures.end())
    {
        printf("Creating BLANK texture.\n");

        SDL_Texture *tex = nullptr;
        SDL_Surface *s;

        s = SDL_CreateRGBSurface(0, 128, 128, 32, 0, 0, 0, 0);
        SDL_FillRect(s, NULL, SDL_MapRGBA(s->format, 255, 255, 255, 255));
        /*
        Uint32 rmask, gmask, bmask, amask;
            rmask = 0xff000000;
            gmask = 0x00ff0000;
            bmask = 0x0000ff00;
            amask = 0x000000ff;
        s = SDL_CreateRGBSurface(0, 128, 128, 32, rmask, gmask, bmask, amask);
        */
        if(s == nullptr)
        {
            printf("Error creating BLANK texture. Our last hope failed - nothing is gonna help us now!\n");
            /// error
        }
        else
        {
            if((tex = SDL_CreateTextureFromSurface(_renderer, s)) == nullptr)
            {
                printf("We DON'T have BLANK!!!!!\n");
            }
            else printf("We have BLANK!!!!!\n");

        }
        SDL_FreeSurface(s);

        textures.insert(make_pair("BLANK", tex));
    }
    else printf("BLANK texture already exists\n");
}
