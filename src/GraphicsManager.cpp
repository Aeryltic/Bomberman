#include "GraphicsManager.h"
#include <fstream>

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
    /** uzywana przy ladowaniu obiektow. sprawdza czy juz jest, jesli nie ma probuje zaladowac, jesli nie moze - BLANK */
    Texture *texture;
    texture = 0;
    unordered_map<string,Texture>::const_iterator found = textures.find(path);
    if(found == textures.end()) texture = &(textures["BLANK"]);
    else texture = const_cast<Texture*>(&(found->second));
    return texture;
}

Texture *GraphicsManager::getTexture(const char *path)
{
    string tmp(path);
    return getTexture(tmp);
}

int GraphicsManager::loadTextures(const char *reference_file_path)
{
    /** to nie bedzie tak dzialac, przebudowac do ladowania konkretnej tekstury, albo jeszcze inaczej */
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

int GraphicsManager::loadTexture(const char *tex_path)
{

    return 0;
}

void GraphicsManager::createBlankTexture()
{

}
