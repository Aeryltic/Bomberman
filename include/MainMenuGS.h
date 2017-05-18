#ifndef MAINMENUGS_H
#define MAINMENUGS_H

#include "GameState.h"

class MainMenuGS : public GameState
{
public:
    MainMenuGS();
    virtual ~MainMenuGS();

    void init();
    void cleanup();
    /*
            void pause();
            void resume();
    */
    /*
            void handleEvents(GameEngine* game);
            void update(GameEngine* game);
            void draw(GameEngine* game);
            */
protected:

private:
};

#endif // MAINMENUGS_H
