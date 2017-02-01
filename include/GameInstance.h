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
        void pause(){_paused = !_paused;}
    protected:

    private:
        GameInstance();
        bool _working;
        bool _paused;
};

#endif // GAMEINSTANCE_H
