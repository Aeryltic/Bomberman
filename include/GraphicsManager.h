#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

/* przechowuje i zarzadza teksturami */

#include <unordered_map>
#include "Texture.h"
#include "AppWindow.h"
#include "Constants.h"

using namespace std;
class GraphicsManager
{
    class Texture
    {
        public:
            Texture(SDL_Texture *texture = nullptr) {/*printf("new Texture\n"); */_texture = texture;}
            ~Texture(){/*printf("delete Texture\n");*/SDL_DestroyTexture(_texture);}
            SDL_Texture *texture(){return _texture;}
        private:
            SDL_Texture *_texture;
    };
    public:
       // GraphicsManager();
        GraphicsManager(SDL_Renderer *renderer);
        virtual ~GraphicsManager();
        SDL_Texture *getTexture(const string &path);
        SDL_Texture *getTexture(const char *path);
     //   int loadTextures(const char *reference_file_path);
        void createBlankTexture();
        bool loadTexture(string tex_path);
        int copyTexToRenderer(const char *tex, SDL_Rect *rect);

        bool isActive(){return _active;}
    protected:

    private:
        bool _active;
        /* pierwsza wygenerowac jako BLANK */
       // unordered_map <string,Texture> textures;
       //unordered_map <string,SDL_Texture*> textures;
       unordered_map <string, shared_ptr<Texture>> textures;
       /// unordered_map <string,shared_ptr<Texture>> _textures; /// tak to powinno wygladac (powinno?)
        SDL_Renderer *_renderer;
};

#endif // GRAPHICSMANAGER_H
