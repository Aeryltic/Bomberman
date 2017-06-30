#include "Message.h"

Message::Message(unsigned type, std::weak_ptr<Entity> publisher) :
    type(type), publisher(publisher) {}

Message::~Message() { }
