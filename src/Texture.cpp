#include "Texture.h"
Texture::Texture()
{
    _texture = nullptr;
}
/*
Texture::Texture(SDL_Renderer *renderer)
{
    /// BLANK texture
    SDL_Surface *tmp;
    Uint32 rmask, gmask, bmask, amask;
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
    tmp = SDL_CreateRGBSurface(0, 64, 64, 32, rmask, gmask, bmask, amask);
    if(tmp == nullptr)
    {
        /// error
    }
    else
    {
        _texture = SDL_CreateTextureFromSurface(renderer, tmp);
    }
    SDL_FreeSurface(tmp);
}
Texture::Texture(SDL_Renderer *renderer, const string &path)
{
    //Load image at specified path
    SDL_Surface *tmp = IMG_Load(path.c_str());
    if(tmp == nullptr)
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        _texture = SDL_CreateTextureFromSurface(renderer, tmp);
    }
    SDL_FreeSurface(tmp);
}
Texture::Texture(SDL_Renderer *renderer, Uint32 color, int w, int h)
{
    /// creates texture filled with color
}
*/
Texture::~Texture()
{
    SDL_DestroyTexture(_texture);
}
