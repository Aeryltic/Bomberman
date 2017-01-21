#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>

class Texture
{
    public:
        Texture(string path);
        Texture(Uint32 color, int w, int h);
        virtual ~Texture();

    protected:

    private:
        SDL_Surface *surface;
};

#endif // TEXTURE_H
