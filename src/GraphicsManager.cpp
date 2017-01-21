#include "GraphicsManager.h"

GraphicsManager::GraphicsManager()
{
    //ctor
}

GraphicsManager::~GraphicsManager()
{
    //dtor
    textures.clear();
}
Texture *GraphicsManager::getTexture(const string &path)
{
    return getTexture(path.c_str());
}

Texture *GraphicsManager::getTexture(const char *path)
{
    Texture *texture;
    texture = 0;
    /* sprawdza czy jest, jesli nie to dodaje, jesli nie ma takiego pliku zwraca BLANK (wygenerowana) czy cos w tym stylu



    */
    return texture;
}
