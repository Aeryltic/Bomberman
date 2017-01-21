#ifndef OBJECTINSTANCE_H
#define OBJECTINSTANCE_H


class ObjectInstance
{
    public:
        ObjectInstance();
        virtual ~ObjectInstance();
        void update(int time_passed);
        void update_position(int time_passed);
    protected:

    private:
        double _posX, _posY, _vX, _vY;
};

#endif // OBJECTINSTANCE_H
