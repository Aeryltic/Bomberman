#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <GraphicsManager.h>
#include <AudioManager.h>

class ResourceManager
{
    public:
        ResourceManager();
        virtual ~ResourceManager();
    protected:

    private:
        GraphicsManager graphicsManager;
        AudioManager audioManager;
};

#endif // RESOURCEMANAGER_H
