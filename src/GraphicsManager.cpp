#include "GraphicsManager.h"
#include <fstream>
#include <SDL_image.h>
GraphicsManager::GraphicsManager(){
    printf("new GraphicsManager\n");
    _renderer = nullptr;
    _active = false;
}
void GraphicsManager::init(SDL_Renderer *renderer){
    _renderer = renderer;
    if(_renderer){
        _active = true;
    }
}
GraphicsManager::~GraphicsManager(){
    printf("delete GraphicsManager\n");
}
SDL_Texture *GraphicsManager::getTexture(const string &path){
    // uzywana przy ladowaniu obiektow. sprawdza czy juz jest, jesli nie ma probuje zaladowac, jesli nie moze - BLANK
    SDL_Texture *texture;
    texture = 0;

    unordered_map<string, shared_ptr<Texture>>::iterator found = _textures.find(path);
    if(found == _textures.end()){
        printf("Texture: %s not found. Loading texture.\n", path.c_str());
        loadTexture(path);
    }
    texture = _textures[path]->texture();
    if(texture == nullptr) texture = _textures[BLANK_TEX]->texture(); // if doesn't exist

    return texture;
}

SDL_Texture *GraphicsManager::getTexture(const char *path){
    string tmp(path);
    return getTexture(tmp);
}

bool GraphicsManager::loadTexture(string texture_path){
    if(_textures.find(texture_path) == _textures.end()){
        printf("Loading texture: %s\n", texture_path.c_str());
        SDL_Texture* newTexture = nullptr;

        SDL_Surface* loadedSurface = IMG_Load(texture_path.c_str());
        if(loadedSurface == nullptr){
            printf("Unable to load image %s! SDL_image Error: %s\n", texture_path.c_str(), IMG_GetError());
        }else{
            newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
            SDL_FreeSurface(loadedSurface);

            if(newTexture == nullptr){
                printf("Unable to create texture from %s! SDL Error: %s\n", texture_path.c_str(), SDL_GetError());
            }

        }
        _textures.insert(make_pair(texture_path, make_shared<Texture>(newTexture)));
        if(newTexture){
            printf("Texture loaded.\n");
            return 1;
        }
        printf("Errors occurred while loading texture.\n");
        return 0;
    }
    printf("Can't load %s - already exists.\n",texture_path.c_str());
    return 0;
}

void GraphicsManager::createBlankTexture()
{
    if(_textures.find(BLANK_TEX) == _textures.end()){
        printf("Creating BLANK texture.\n");

        SDL_Texture *tex = nullptr;
        SDL_Surface *s;

        s = SDL_CreateRGBSurface(0, 128, 128, 32, 0, 0, 0, 0);
        SDL_FillRect(s, NULL, SDL_MapRGBA(s->format, 255, 100, 255, 255));

        if(s == nullptr){
            printf("Error creating BLANK texture. Our last hope failed - nothing is gonna help us now!\n");
            /// error
        }else{
            if((tex = SDL_CreateTextureFromSurface(_renderer, s)) == nullptr){
                printf("We DON'T have BLANK!!!!!\n");
            }
            else printf("We have BLANK!!!!!\n");
        }
        SDL_FreeSurface(s);

        _textures.insert(make_pair(BLANK_TEX, make_shared<Texture>(tex)));
    }
    else printf("BLANK texture already exists\n");
}
/*
int GraphicsManager::copyTexToRenderer(const char *tex, SDL_Rect *rect)
{
    return SDL_RenderCopy(_renderer, _textures[tex], NULL, rect);
}
*/
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
