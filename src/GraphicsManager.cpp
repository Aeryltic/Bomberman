#include "GraphicsManager.h"
#include <fstream>
GraphicsManager::GraphicsManager()
{
    _renderer = nullptr;
}
GraphicsManager::GraphicsManager(SDL_Renderer *renderer)
{
    _renderer = renderer;
    createBlankTexture();
    //ctor
}

GraphicsManager::~GraphicsManager()
{
    //dtor
    /*
    textures.clear();
    */
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
        if(loadTexture(path) == 0)
        {
            texture = textures[path];
        }
        else
        {
            //texture = &(textures["BLANK"]);
            printf("Not found - giving BLANK.\n");
            return textures["BLANK"];//.SDL_Tex();
        }
    }
    else
    {
        texture = found->second;//&(found->second);
    }
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
int GraphicsManager::loadTexture(string texture_path)
{
    /*
    if(textures.find(texture_path) == textures.end())
        textures[texture_path] = Texture(_renderer, texture_path);
        */

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( texture_path.c_str() );
    if( loadedSurface == nullptr )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", texture_path.c_str(), IMG_GetError() );
        return -1;
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( _renderer, loadedSurface );
        SDL_FreeSurface( loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", texture_path.c_str(), SDL_GetError() );
            return -1;
        }
    }
    //textures[texture_path] = Texture(newTexture);
    textures[texture_path] = newTexture;
    return 0;
}

void GraphicsManager::createBlankTexture()
{
    if(textures.find("BLANK") == textures.end())
    {
        printf("Creating BLANK texture.\n");

        SDL_Texture *tex = nullptr;
        SDL_Surface *s;
        s = SDL_CreateRGBSurface(0, 128, 128, 32, 0, 0, 0, 0);

        /* Filling the surface with green color. */
        SDL_FillRect(s, NULL, SDL_MapRGBA(s->format, 255, 255, 255, 255));
        if(s == nullptr)
        {
            printf("Error creating BLANK texture. Our last hope failed - nothing is gonna help us now!\n");
            /// error
        }
        else
        {
            if((tex = SDL_CreateTextureFromSurface(_renderer, s))==nullptr)
            {
                printf("We DON'T have BLANK!!!!!\n");
            }
            else printf("We have BLANK!!!!!\n");

        }
        SDL_FreeSurface(s);

       // textures["BLANK"] = Texture(tex);
        textures["BLANK"] = tex;
        /*
        SDL_Surface *s;
        s = SDL_CreateRGBSurface(0, 128, 128, 32, 0, 0, 0, 0);
        SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 255, 50, 50));
        textures["BLANK"] = TextureSDL_CreateTextureFromSurface( _renderer, s );
        */
    }

}
