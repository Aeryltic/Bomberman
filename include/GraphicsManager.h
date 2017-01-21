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
        virtual ~GraphicsManager();
        Texture *getTexture(const string &path);
        Texture *getTexture(const char *path);

    protected:

    private:

        /* pierwsza wygenerowac jako BLANK */
        unordered_map <string,Texture> textures;
};

#endif // GRAPHICSMANAGER_H
