#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

/* posiada i zarzadza ekranem, przechowuje tekstury, wyswietla */

#include <unordered_map>
#include "Texture.h"
using namespace std;
class GraphicsManager
{
    public:
        GraphicsManager();
        virtual ~GraphicsManager();
        Texture *getTexture(string path);
    protected:

    private:
        unordered_map <string,Texture> textures;
};

#endif // GRAPHICSMANAGER_H
