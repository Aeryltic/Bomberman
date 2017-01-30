#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

class GameInstance
{
    public:

        virtual ~GameInstance();
        static GameInstance &getInstance();
        int run();
        int init();
        int startGame();

        void quit();
    protected:

    private:
        GameInstance();
        bool _working;
};

#endif // GAMEINSTANCE_H
