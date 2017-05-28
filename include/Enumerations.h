#ifndef ENUMERATIONS_H_INCLUDED
#define ENUMERATIONS_H_INCLUDED

enum EventType
{
    EVENT_LOST = 0,
    EVENT_WON,
    EVENT_REMOVE,
    EVENT_ADD,
    EVENT_PAUSE,
    EVENT_CONSOLE_TOGGLE,
    EVENT_TIME_UPDATE,


    NUMEVENTS   /// to ma tu być
};

enum BoxPosition
{
    POS_CENTER,
    POS_LEFT,
    POS_RIGHT,
    POS_TOP,
    POS_BOTTOM,
    POS_LEFT_TOP,
    POS_RIGHT_TOP,
    POS_LEFT_BOTTOM,
    POS_RIGHT_BOTTOM
};

enum ConsumableType
{
    CONSUMABLE_FOOD,
    CONSUMABLE_WATER
};

enum ScentType
{
    SCENT_FOOD,
    SCENT_NEST,
    SCENT_DANGER
};

enum MessageType
{
    MSG_COLLISION,
    MSG_ACTIVATION,

    MSG_SCANNING,
    MSG_TARGET,
    //-----------------
    MSG_GOOD_DIRECTION,
    MSG_BAD_DIRECTION,
    MSG_LOOK_FOR_FOOD,
    MSG_LOOK_FOR_NEST,
    MSG_IM_EDIBLE,
    MSG_IM_CARRYABLE
};

/*
enum KeyStatus
{
    KEY_NONE = 0,
    KEY_PRESSED = 1,
    KEY_DOWN = 2,
    KEY_RELEASED = 4,
    KEY_UP = 8
};
*/
#endif // ENUMERATIONS_H_INCLUDED
