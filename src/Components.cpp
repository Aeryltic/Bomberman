//#include "Components.h"
//int _AliveCount=0;
//
///*
///// PlayerControllerComponent ---------------------------------------------------------------------------
//void PlayerControllerComponent::setActive()
//{
//    if(target()->has<PhysicalForm>() && (_iManager != nullptr))
//        _active = true;
//}
//void PlayerControllerComponent::work(int ms)
//{
//    int up_down = 0,
//        left_right = 0;
//    if(_iManager->keyStatus(SDLK_w) & (KEY_PRESSED|KEY_DOWN))   // go up
//    {
//        up_down = -1;
//    }
//    else if(_iManager->keyStatus(SDLK_s) & (KEY_PRESSED|KEY_DOWN))  // go down
//    {
//        up_down = 1;
//    }
//    if(_iManager->keyStatus(SDLK_a) & (KEY_PRESSED|KEY_DOWN))  // go left
//    {
//        left_right = -1;
//    }
//    else if(_iManager->keyStatus(SDLK_d) & (KEY_PRESSED|KEY_DOWN))  // go right
//    {
//        left_right = 1;
//    }
//
//    if(up_down || left_right)
//    {
//        target()->get<PhysicalForm>()->setAngle(atan2(up_down,left_right));
//        //_target->get<PhysicalForm>()->setSpeedToMax();
//        target()->get<PhysicalForm>()->accelerate(ms);
//    }
//    else target()->get<PhysicalForm>()->deccelerate(ms);//_target->get<PhysicalForm>()->setSpeed(0);
//    // bomb dropping
//    if(_iManager->keyStatus(SDLK_SPACE) & (KEY_PRESSED))    // drop bomb
//    {
//            /// DROP THAT BOMB
//    }
//}
//*/
///// class World
//int_vector2d World::getNearestCellCoorFromGivenPosInGivenDirection(int_vector2d pos, int dir)
//{
//    int_vector2d c =  pos;
//    if(valid(c.x,c.y))
//    {
//        int dx = c.x, dy = c.y;
//        if(dir == DIR_UP)
//            dy--;
//        else if(dir == DIR_DOWN)
//            dy++;
//        else if(dir == DIR_LEFT)
//            dx--;
//        else if(dir == DIR_RIGHT)
//            dx++;
//        if(valid(dx,dy))
//        {
//            if((_square[dy][dx].lock()->get<SquareCell>()->getType() == CELL_FLOOR) && (_square[dy][dx].lock()->get<SquareCell>()->available()))
//            //if(((run(_square[dy][dx].lock(), SquareCell, getType)) == CELL_FLOOR) && (run(_square[dy][dx].lock(), SquareCell, available())))
//            {
//                return int_vector2d(dx,dy);//realFromGrid(dx,dy);
//            }
//        }
//    }
//    return pos;
//}
//bool World::isDangerous(int x, int y)
//{
//    return 0;//_square[y][x]->has<Dangerous>();
//}
//
//void World::setSafe(int x,int y){_square[y][x].lock()->get<SquareCell>()->setSafe();}
//void World::setUnsafe(int x,int y){_square[y][x].lock()->get<SquareCell>()->setUnsafe();}
//
//bool World::isSafe(int x, int y){if(valid(x,y))return _square[y][x].lock()->get<SquareCell>()->isSafe();return false;}
//bool World::isSafe(int_vector2d p){if(valid(p.x,p.y))return _square[p.y][p.x].lock()->get<SquareCell>()->isSafe();return false;}
//
//void World::blockCell(int x, int y){if(valid(x,y))getCell(x,y)->get<SquareCell>()->block();}
//void World::unblockCell(int x, int y){if(valid(x,y))getCell(x,y)->get<SquareCell>()->unblock();}
//
//void World::destroyDirt(int x, int y, EntityManager *entityManager)
//{
//    if(valid(x,y))
//    {
//        if(_square[y][x].lock()->get<SquareCell>()->getType() == CELL_DIRT)
//        {
//            _square[y][x].lock()->deactivate();
//            _square[y][x].reset();
//            addCell(entityManager->getFactory()->createWorldCell(x, y, CELL_FLOOR));
//        }
//    }
//}
//
//bool World::addCell(entity_ptr cell)//, int x, int y)
//{
//    if(cell->has<SquareCell>() && cell->get<PhysicalForm>())
//    {
//        int_vector2d pos = cell->get<PhysicalForm>()->getGridPos();
//        if(valid(pos.x,pos.y))
//        {
//            _square[pos.y][pos.x] = cell;
//            return true;
//        }
//    }
//    return false;
//}
///// class KeyboardController
//void KeyboardController::setActive()
//{
//    if(target()->has<PhysicalForm>() && (_iManager != nullptr))
//        _active = true;
//}
//
//
///// class MovementController
//bool MovementController::destReached()
//{
//   // printf("MovementController::destReached()...\n");
//   vector2d c = current();
//    if(_reached || (c - _dest < 1.0))
//    {
//        _reached = true;
//        return 1;
//    }
//    //if(_target->get<PhysicalForm>()->getPos() - _dest->coor() < 1.0) return 1;
//    return 0;
//}
//
//void MovementController::setActive()
//{
// //   printf("MovementController::setActive()\n");
//    if(target()->has<PhysicalForm>())
//    {
//        _physicalForm = target()->get<PhysicalForm>();
//        _dest = _physicalForm->getPos();
//        _active = true;
//      //  printf("----Movement Controller Active\n");
//    }
//}
//
//void MovementController::work(int ms) // kierowanie ruchu postaci
//{
//    //PhysicalForm *physicalForm = _target->get<PhysicalForm>();
//    if(_moving)
//    {
//        if(!destReached())
//        {
//            vector2d c = current(),
//                     d = _dest;
//            _physicalForm->setAngle(atan2(d.y-c.y, d.x-c.x));
//            //_physicalForm->accelerate(ms);
//            _physicalForm->setSpeedToMax();
//        }
//        else
//        {
//            if(_readyToStop)
//            {
//                _physicalForm->setSpeed(0);
//                _moving = false;
//            }
//            _readyToStop = true;
//        }
//    }
//
//}
//void MovementController::setDest(vector2d dest)
//{
//  //  printf("MovementController::setDest(%lfx%lf)...\n", dest.x, dest.y);
//    if(destReached())
//    {
//        /*
//        NavNode *_newDest = _current->getNeighbour(dir);
//        if(_newDest) _dest = _newDest;
//            */
//        if(dest != _dest)
//        {
//            _dest.x=dest.x;
//            _dest.y = dest.y;
//            _readyToStop = false;
//            _reached = false;
//            _moving = true;
//        }
//
//       // printf("dest SET\n");
//    }
//}
//vector2d MovementController::current()
//{
//    /*printf("MovementController::current()\n");*/
//    return target()->get<PhysicalForm>()->getPos();
//}
//
///// class Player
//Player::~Player()
//{
//    printf("PRZEGRALES\n"); /// trzeba doprawcowac by nie wysylal zawsze jak koncze gre (bo wysyla nawet jak wygram)
//    EventManager::pushUserEvent(EVENT_LOST,nullptr,nullptr);
//}
//
///// class Enemy
//int Enemy::_count = 0;
//Enemy::~Enemy()
//{
//    _count--;
//    if(_count<=0)
//    {
//        printf("WYGRALES\n");
//        EventManager::pushUserEvent(EVENT_WON, nullptr, nullptr);
//    }
//}
//
//
///*
//NavNode *NavNode::getNeighbour(int dir)
//{
//    if(_linked.find(dir)!=_linked.end())
//    {
//        return _linked[dir];
//    }
//    return nullptr;
//}
//*/
///*
//void NavNode::setLink(int dir, NavNode *node)
//{
//    _linked.insert(make_pair(dir,node));
//}
//*/
///*
//vector2d NavNode::coor()
//{
//    vector2d v = target()->get<PhysicalForm>()->getPos();
//    return v;
//}
//*/
//
////int Alive::_count=0;
