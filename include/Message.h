#ifndef MESSAGE_H
#define MESSAGE_H

#include <memory>
class Entity;

struct Message {
    Message(unsigned type, std::weak_ptr<Entity> publisher);
    virtual ~Message();

    unsigned type;
    std::weak_ptr<Entity> publisher;
};

#endif // MESSAGE_H
