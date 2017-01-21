#include "Texture.h"

Texture::Texture(string path)
{
    //Load image at specified path
    surface = IMG_Load(path.c_str());
    if(surface == NULL)
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    /** jeszcze trzeba tu stworzyc SDL_Texture i dopiero na tym pracowac */
    /*
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    */
}
Texture::Texture(Uint32 color, int w, int h)
{
    /** creates texture filled with color */
}
Texture::~Texture()
{
    SDL_FreeSurface(surface);
}
