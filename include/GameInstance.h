#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

class GameInstance
{
    public:
        GameInstance();
        virtual ~GameInstance();
        int run();
        int init();
        int startGame();
    protected:

    private:
};

#endif // GAMEINSTANCE_H
