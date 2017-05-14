#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameInstance;

class GameState
{
public:
    GameState() {}
    virtual ~GameState(){}
    virtual void run() = 0;

    virtual void init() = 0;
    virtual void cleanup() = 0;
/*
    virtual void pause() = 0;
    virtual void resume() = 0;
*/
/*
    void changeState(GameInstance* game, GameState* state)
    {
        game->changeState(state);
    }
*/
protected:

    virtual void handleEvents(GameInstance* game) = 0;
    virtual void update(GameInstance* game) = 0;
    virtual void draw(GameInstance* game) = 0;
};

#endif // GAMESTATE_H
