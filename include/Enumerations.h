#ifndef ENUMERATIONS_H_INCLUDED
#define ENUMERATIONS_H_INCLUDED

enum KeyStatus
{
    KEY_NONE = 0,
    KEY_PRESSED = 1,
    KEY_DOWN = 2,
    KEY_RELEASED = 4,
    KEY_UP = 8
};

enum ObjectType
{
    OBJECT_NONE = 0,
    OBJECT_REAL,
    OBJECT_ABSTRACT,
    OBJECT_LIVING,
    OBJECT_FIELD,
    OBJECT_BOARD
};

enum Direction
{
    DIR_NONE = 0,
    DIR_UP,
    DIR_RIGHT,
    DIR_DOWN,
    DIR_LEFT,
    DIR_MAX
};

enum WorldCellType
{
    CELL_NONE = 0,
    CELL_FLOOR,
    CELL_WALL,
    CELL_DIRT
};

enum EventType
{
    EVENT_LOST = 0,
    EVENT_WON,


    NUMEVENTS
};

#endif // ENUMERATIONS_H_INCLUDED
