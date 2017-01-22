#ifndef KEYSTATUS_H
#define KEYSTATUS_H

enum
class KeyStatus
{
    public:
        KeyStatus();
        virtual ~KeyStatus();

    protected:

    private:
        bool    _down,
                _up,
                _push,
                _release;
};

#endif // KEYSTATUS_H
