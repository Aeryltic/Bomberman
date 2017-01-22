#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
using namespace std;
class Texture
{
    public:
        Texture();
        Texture(SDL_Renderer *renderer);
        Texture(SDL_Renderer *renderer, const string &path);
        Texture(SDL_Renderer *renderer, Uint32 color, int w, int h);
        virtual ~Texture();

    protected:

    private:
        SDL_Texture *_texture;
     //   SDL_Surface *surface;
};

#endif // TEXTURE_H
