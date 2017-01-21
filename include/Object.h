#ifndef OBJECT_H
#define OBJECT_H


class Object
{
    public:
        Object();
        virtual ~Object();
        virtual void update(int time_passed);
    protected:

    private:
        string _name;
        // predkosc  w pikselach lub metrach na sekunde
};

#endif // OBJECT_H
