#include "Component.h"
#include "InputManager.h"
#include "Entity.h"
#include <cmath>
#include "EntityManager.h"
#include "ObjectFactory.h"
#include "EventManager.h"
#include "MiscFunctions.h"

int _AliveCount=0;
/// PhysicalFormComponent ---------------------------------------------------------------------------
void PhysicalFormComponent::work(int ms)
{
    if(!_static)
    {
        if(_v >= 0.00001)
        {
            double  mx = cos(_angle) * _v / 1000.0 * ms,
                    my = sin(_angle) * _v / 1000.0 * ms;
            moveBy(mx,my);
            //printPos();
        }
       // else printf("not moving\n");
    }
   // else printf("static\n");
}
SDL_Rect PhysicalFormComponent::rect(int ms)
{
    SDL_Rect rect = {.x = (int)_x, .y = (int)_y, .w = (int)_w, .h = (int)_h};
    rect.x += cos(_angle) * _v * ms / 1000.0;
    rect.y += sin(_angle) * _v * ms / 1000.0;
    return rect;
}
/// PlayerControllerComponent ---------------------------------------------------------------------------
void PlayerControllerComponent::setActive()
{
    if(target()->hasComponent<PhysicalFormComponent>() && (_iManager != nullptr))
        _active = true;
}
void PlayerControllerComponent::work(int ms)
{
    int up_down = 0,
        left_right = 0;
    if(_iManager->keyStatus(SDLK_w) & (KEY_PRESSED|KEY_DOWN))   // go up
    {
        up_down = -1;
    }
    else if(_iManager->keyStatus(SDLK_s) & (KEY_PRESSED|KEY_DOWN))  // go down
    {
        up_down = 1;
    }
    if(_iManager->keyStatus(SDLK_a) & (KEY_PRESSED|KEY_DOWN))  // go left
    {
        left_right = -1;
    }
    else if(_iManager->keyStatus(SDLK_d) & (KEY_PRESSED|KEY_DOWN))  // go right
    {
        left_right = 1;
    }

    if(up_down || left_right)
    {
        target()->getComponent<PhysicalFormComponent>()->setAngle(atan2(up_down,left_right));
        //_target->getComponent<PhysicalFormComponent>()->setSpeedToMax();
        target()->getComponent<PhysicalFormComponent>()->accelerate(ms);
    }
    else target()->getComponent<PhysicalFormComponent>()->deccelerate(ms);//_target->getComponent<PhysicalFormComponent>()->setSpeed(0);
    // bomb dropping
    if(_iManager->keyStatus(SDLK_SPACE) & (KEY_PRESSED))    // drop bomb
    {
            /// DROP THAT BOMB
    }
}

bool World::addCell(entity_ptr cell)//, int x, int y)
{
    if(cell->hasComponent<SquareCell>() && cell->getComponent<PhysicalFormComponent>())
    {
        int_vector2d pos = cell->getComponent<PhysicalFormComponent>()->getGridPos();
        if(valid(pos.x,pos.y))
        {
            _square[pos.y][pos.x] = cell;
            return true;
        }
    }
    return false;
}

bool MovementController::destReached()
{
   // printf("MovementController::destReached()...\n");
   vector2d c = current();
    if(_reached || (c - _dest < 1.0))
    {
        _reached = true;
        return 1;
    }
    //if(_target->getComponent<PhysicalFormComponent>()->getPos() - _dest->coor() < 1.0) return 1;
    return 0;
}

void MovementController::setActive()
{
 //   printf("MovementController::setActive()\n");
    if(target()->hasComponent<PhysicalFormComponent>())
    {
        _physicalForm = target()->getComponent<PhysicalFormComponent>();
        _dest = _physicalForm->getPos();
        _active = true;
      //  printf("----Movement Controller Active\n");
    }
}

void MovementController::work(int ms) // kierowanie ruchu postaci
{
    //PhysicalFormComponent *physicalForm = _target->getComponent<PhysicalFormComponent>();
    if(_moving)
    {
        if(!destReached())
        {
            vector2d c = current(),
                     d = _dest;
            _physicalForm->setAngle(atan2(d.y-c.y, d.x-c.x));
            //_physicalForm->accelerate(ms);
            _physicalForm->setSpeedToMax();
        }
        else
        {
            if(_readyToStop)
            {
                _physicalForm->setSpeed(0);
                _moving = false;
            }
            _readyToStop = true;
        }
    }

}
void MovementController::setDest(vector2d dest)
{
  //  printf("MovementController::setDest(%lfx%lf)...\n", dest.x, dest.y);
    if(destReached())
    {
        /*
        NavNode *_newDest = _current->getNeighbour(dir);
        if(_newDest) _dest = _newDest;
            */
        if(dest != _dest)
        {
            _dest.x=dest.x;
            _dest.y = dest.y;
            _readyToStop = false;
            _reached = false;
            _moving = true;
        }

       // printf("dest SET\n");
    }
}
void KeyboardController::setActive()
{
    if(target()->hasComponent<PhysicalFormComponent>() && (_iManager != nullptr))
        _active = true;
}

int_vector2d World::getNearestCellCoorFromGivenPosInGivenDirection(int_vector2d pos, int dir)
{
    int_vector2d c =  pos;
    if(valid(c.x,c.y))
    {
        int dx = c.x, dy = c.y;
        if(dir == DIR_UP)
            dy--;
        else if(dir == DIR_DOWN)
            dy++;
        else if(dir == DIR_LEFT)
            dx--;
        else if(dir == DIR_RIGHT)
            dx++;
        if(valid(dx,dy))
        {
            if((_square[dy][dx].lock()->getComponent<SquareCell>()->getType() == CELL_FLOOR) && (_square[dy][dx].lock()->getComponent<SquareCell>()->available()))
            {
                return int_vector2d(dx,dy);//realFromGrid(dx,dy);
            }
        }
    }
    return pos;
}
bool World::isDangerous(int x, int y)
{
    return 0;//_square[y][x]->hasComponent<Dangerous>();
}

vector2d MovementController::current()
{
    /*printf("MovementController::current()\n");*/
    return target()->getComponent<PhysicalFormComponent>()->getPos();
}

void World::destroyDirt(int x, int y, EntityManager *entityManager, ObjectFactory *objectFactory)
{
    if(valid(x,y))
    {
        if(_square[y][x].lock()->getComponent<SquareCell>()->getType() == CELL_DIRT)
        {
            _square[y][x].lock()->deactivate();
            _square[y][x].reset();
            addCell(objectFactory->createWorldCell(x, y, CELL_FLOOR));
        }
    }
}

void World::setSafe(int x,int y){_square[y][x].lock()->getComponent<SquareCell>()->setSafe();}
void World::setUnsafe(int x,int y){_square[y][x].lock()->getComponent<SquareCell>()->setUnsafe();}

bool World::isSafe(int x, int y){if(valid(x,y))return _square[y][x].lock()->getComponent<SquareCell>()->isSafe();return false;}
bool World::isSafe(int_vector2d p){if(valid(p.x,p.y))return _square[p.y][p.x].lock()->getComponent<SquareCell>()->isSafe();return false;}

void World::blockCell(int x, int y){if(valid(x,y))getCell(x,y)->getComponent<SquareCell>()->block();}
void World::unblockCell(int x, int y){if(valid(x,y))getCell(x,y)->getComponent<SquareCell>()->unblock();}

Player::~Player()
{
    printf("PRZEGRALES\n"); /// trzeba doprawcowac by nie wysylal zawsze jak koncze gre (bo wysyla nawet jak wygram)
    EventManager::pushUserEvent(EVENT_LOST,nullptr,nullptr);
}
int Enemy::_count = 0;
Enemy::~Enemy()
{
    _count--;
    if(_count<=0)
    {
        printf("WYGRALES\n");
        EventManager::pushUserEvent(EVENT_WON, nullptr, nullptr);
    }
}

/*
void KeyboardController::work(int ms)
{

    Direction dir = DIR_NONE;
    if(_iManager->keyStatus(SDLK_w) & (KEY_PRESSED|KEY_DOWN))   // go up
    {
        dir = DIR_UP;
        printf("going up\n");
    }
    else if(_iManager->keyStatus(SDLK_s) & (KEY_PRESSED|KEY_DOWN))  // go down
    {
        dir = DIR_DOWN;
        printf("going down\n");
    }
    if(_iManager->keyStatus(SDLK_a) & (KEY_PRESSED|KEY_DOWN))  // go left
    {
        dir = DIR_LEFT;
        printf("going left\n");
    }
    else if(_iManager->keyStatus(SDLK_d) & (KEY_PRESSED|KEY_DOWN))  // go right
    {
        dir = DIR_RIGHT;
        printf("going right\n");
    }

    if(dir)
    {
        _target->getComponent<MovementController>()->setDest(dir);
    }
    //else _target->getComponent<PhysicalFormComponent>()->deccelerate(ms);//_target->getComponent<PhysicalFormComponent>()->setSpeed(0);
    // bomb dropping
    if(_iManager->keyStatus(SDLK_SPACE) & (KEY_PRESSED))    // drop bomb
    {
            /// DROP THAT BOMB
    }

}
*/
/*
NavNode *NavNode::getNeighbour(int dir)
{
    if(_linked.find(dir)!=_linked.end())
    {
        return _linked[dir];
    }
    return nullptr;
}
*/
/* // obsolete
void World::setup()
{
    printf("World::setup()...\n");

    for(int i=0; i<_h; i++)
    {
        for(int j=0; j<_w; j++)
        {
            entity_ptr current_grid = _square[y][x].lock();
            int y = i, x = j;
//            if(_square[y][x]->hasComponent<NavNode>())
            if(current_grid->getComponent<SquareCell>()->getType() == CELL_FLOOR)
            {
                int ny = y-1, nx = x;
                if(valid(nx,ny) && _square[ny][nx].lock()->getComponent<SquareCell>()->available())
                    _square[y][x]->getComponent<NavNode>()->setLink(DIR_UP, _square[ny][nx].lock()->getComponent<NavNode>());

                ny = y+1, nx = x;
                if(valid(nx,ny) && _square[ny][nx].lock()->getComponent<SquareCell>()->available())
                    _square[y][x]->getComponent<NavNode>()->setLink(DIR_DOWN, _square[ny][nx].lock()->getComponent<NavNode>());

                ny = y, nx = x-1;
                if(valid(nx,ny) && _square[ny][nx].lock()->getComponent<SquareCell>()->available())
                    _square[y][x]->getComponent<NavNode>()->setLink(DIR_LEFT, _square[ny][nx].lock()->getComponent<NavNode>());

                ny = y, nx = x+1;
                if(valid(nx,ny) && _square[ny][nx].lock()->getComponent<SquareCell>()->available())
                    _square[y][x]->getComponent<NavNode>()->setLink(DIR_RIGHT, _square[ny][nx].lock()->getComponent<NavNode>());
            }
        }
    }
}
*/
/*
void NavNode::setLink(int dir, NavNode *node)
{
    _linked.insert(make_pair(dir,node));
}
*/
/*
vector2d NavNode::coor()
{
    vector2d v = target()->getComponent<PhysicalFormComponent>()->getPos();
    return v;
}
*/
/*
void PlayerControllerComponent::setActive()
{
    if((_iManager != nullptr) && (_target->getComponent<MovementComponent>())) /// potrzebuje klawiatury i jego target musi umiec sie poruszac
    {
        _active = true;
    }
}
*/
//int Alive::_count=0;
