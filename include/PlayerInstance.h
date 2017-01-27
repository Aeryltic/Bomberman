#ifndef PLAYERINSTANCE_H
#define PLAYERINSTANCE_H

#include <ObjectInstance.h>


class PlayerInstance : public ObjectInstance
{
    public:
        PlayerInstance(const Object &base, int x, int y);
        virtual ~PlayerInstance();

    protected:

    private:
};

#endif // PLAYERINSTANCE_H
