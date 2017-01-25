#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

/* przechowuje i zarzadza teksturami */

#include <unordered_map>
#include "Texture.h"
#include "AppWindow.h"

using namespace std;
class GraphicsManager
{
    public:
        GraphicsManager();
        GraphicsManager(SDL_Renderer *renderer);
        virtual ~GraphicsManager();
        SDL_Texture *getTexture(const string &path);
        SDL_Texture *getTexture(const char *path);
     //   int loadTextures(const char *reference_file_path);
        void createBlankTexture();
        int loadTexture(string tex_path);
        int copyTexToRenderer(const char *tex, SDL_Rect *rect);
    protected:

    private:

        /* pierwsza wygenerowac jako BLANK */
       // unordered_map <string,Texture> textures;
       unordered_map <string,SDL_Texture*> textures;
        SDL_Renderer *_renderer;
};

#endif // GRAPHICSMANAGER_H
