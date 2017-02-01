#include "ControllingSystem.h"

#include "InputManager.h"
#include "MiscFunctions.h"

ControllingSystem::ControllingSystem(ObjectFactory *objectFactory)
{
    _objectFactory = objectFactory;
}

ControllingSystem::~ControllingSystem()
{
    //dtor
}

void ControllingSystem::update(EntityManager *entityManager, int ms)
{
    entity_ptr world = entityManager->getWorld();
    entity_ptr player = entityManager->getPlayer();
    //printf("player.getID() = %d\n",player->getID());
    for(auto object_m : entityManager->entity())
    {
        entity_ptr object = object_m.second;
       // if(object->isActive())
        {
            if(object->hasComponent<PhysicalFormComponent>())
            {
                if(object->hasComponent<BombPlanter>())
                    object->getComponent<BombPlanter>()->update(ms);

                PhysicalFormComponent *physicalForm = object->getComponent<PhysicalFormComponent>();
                int_vector2d grid_coor = physicalForm->getGridPos();
                physicalForm->update(ms);
                if(object->hasComponent<MovementController>())
                {
                    MovementController *movementController = object->getComponent<MovementController>();
                    movementController->update(ms);


                    /// KeyboardController BEGIN
                    if(object->hasComponent<KeyboardController>())
                    {
                        KeyboardController *controller = object->getComponent<KeyboardController>();
                        InputManager *_iManager = controller->getInputManager();
                        if(movementController->destReached())
                        {

                            Direction dir = DIR_NONE;
                            if(_iManager->keyStatus(SDLK_w) & (KEY_PRESSED|KEY_DOWN))   // go up
                            {
                                dir = DIR_UP;
                            }
                            else if(_iManager->keyStatus(SDLK_s) & (KEY_PRESSED|KEY_DOWN))  // go down
                            {
                                dir = DIR_DOWN;
                            }
                            if(_iManager->keyStatus(SDLK_a) & (KEY_PRESSED|KEY_DOWN))  // go left
                            {
                                dir = DIR_LEFT;
                            }
                            else if(_iManager->keyStatus(SDLK_d) & (KEY_PRESSED|KEY_DOWN))  // go right
                            {
                                dir = DIR_RIGHT;
                            }

                            if(dir)
                            {
                                movementController->setDest(realFromGrid(world->getComponent<World>()->getNearestCellCoorFromGivenPosInGivenDirection(grid_coor,dir)));
                            }
                        }

                        //else _target->getComponent<PhysicalFormComponent>()->deccelerate(ms);//_target->getComponent<PhysicalFormComponent>()->setSpeed(0);
                        // bomb dropping
                        if(object->hasComponent<BombPlanter>())
                        {
                            if(_iManager->keyStatus(SDLK_SPACE) & (KEY_PRESSED|KEY_DOWN))    // drop bomb
                            {
                                BombPlanter *bombPlanter = object->getComponent<BombPlanter>();
                                if(bombPlanter->canPlantNext())
                                {
                                    plantBomb(grid_coor.x, grid_coor.y, bombPlanter, world->getComponent<World>());
                                    /*
                                    for(int i=0;i<world->getComponent<World>()->width();i++)
                                    {
                                        for(int j=0;j<world->getComponent<World>()->height();j++)
                                        {
                                            printf("%d ",world->getComponent<World>()->isSafe(j,i));
                                        }
                                        printf("\n");
                                    }
                                    */
                                }
                            }
                        }

                    }
                    /// END

                    /// AIController BEGIN
                    if(object->hasComponent<AIController>()) /// nie zamykac w klatce 1x1
                    {
                        /// need cleverer AI
                        AIController *controller = object->getComponent<AIController>();
                        if(movementController->destReached())
                        {
                            //int_vector2d curr_pos
                            int dir = controller->getDir();
                            //printf("%d is at %dx%d (%d)\n",object->getID(),grid_coor.x,grid_coor.y,world->getComponent<World>()->isSafe(grid_coor.x,grid_coor.y));
                            if(!world->getComponent<World>()->isSafe(grid_coor.x,grid_coor.y)) /// run away
                            {
                                //printf("%d at %dx%d is not safe, looking for escape plan!\n",object->getID(),grid_coor.x,grid_coor.y);
                                if(!controller->hasPath())
                                {
                                    setRunaway(grid_coor.x, grid_coor.y, controller, world->getComponent<World>());
                                    controller->print();
                                }

                                vector2d new_dest = realFromGrid(controller->nextStop());//world->getComponent<World>()->getNearestCellCoorFromGivenPosInGivenDirection(physicalForm->getPos(),dir);
                                controller->setDir(dir);
                                movementController->setDest(new_dest);
                            }
                            else /// go anywhere safe
                            {
                                controller->clearPath();
                                //printf("free roam at %dx%d\n", grid_coor.x, grid_coor.y);
                                vector2d curr_pos = physicalForm->getPos();
                                vector<int>possible;
                                //bool possible[DIR_MAX] = {false};
                                for(int i=1; i<DIR_MAX; i++) // sprawdzanie gdzie mozna sie ruszyc
                                {
                                    if(curr_pos != realFromGrid(world->getComponent<World>()->getNearestCellCoorFromGivenPosInGivenDirection(grid_coor,i)))possible.push_back(i);
                                }
                                if(possible.size() == 1)
                                {
                                    dir = possible[0];
                                }
                                else
                                {
                                    int opposite = DIR_NONE;
                                    if(dir == DIR_DOWN)opposite = DIR_UP;
                                    else if(dir == DIR_UP)opposite = DIR_DOWN;
                                    else if(dir == DIR_LEFT)opposite = DIR_RIGHT;
                                    else if(dir == DIR_RIGHT)opposite = DIR_LEFT;
                                    for(unsigned i=0; i<possible.size(); i++)
                                    {
                                        if(!world->getComponent<World>()->isSafe(world->getComponent<World>()->getNearestCellCoorFromGivenPosInGivenDirection(grid_coor,dir)))
                                        {
                                            possible.erase(possible.begin() + i);
                                            i--;
                                        }
                                    }
                                    if(possible.size()>1)
                                    {
                                        for(unsigned i=0; i<possible.size(); i++)
                                        {
                                            if(possible[i] == opposite)
                                            {
                                                possible.erase(possible.begin() + i);
                                                i--;
                                                break;
                                            }
                                        }
                                    }
                                    if(possible.size())
                                    {
                                        dir = possible[rand()%possible.size()];
                                    }
                                    else dir = DIR_NONE;

                                }
                                if(dir != DIR_NONE)
                                {
                                    vector2d new_dest = realFromGrid(world->getComponent<World>()->getNearestCellCoorFromGivenPosInGivenDirection(grid_coor,dir));
                                    controller->setDir(dir);
                                    if(world->getComponent<World>()->isSafe(gridFromReal(new_dest)))movementController->setDest(new_dest);
                                    if(object->hasComponent<BombPlanter>())
                                    {
                                        if(itIsAGoodSpotToDropABomb(grid_coor.x, grid_coor.y, world))
                                        {
                                            BombPlanter *bombPlanter = object->getComponent<BombPlanter>();
                                            if(bombPlanter->canPlantNext()) /* plant a bomb  */
                                            {
                                                plantBomb(grid_coor.x, grid_coor.y, bombPlanter, world->getComponent<World>());
                                                /*
                                                for(int i=0;i<world->getComponent<World>()->width();i++)
                                                {
                                                    for(int j=0;j<world->getComponent<World>()->height();j++)
                                                    {
                                                        printf("%d ",world->getComponent<World>()->isSafe(j,i));
                                                    }
                                                    printf("\n");
                                                }
                                                */
                                            }
                                        }
                                    }
                                }

                            }

                        }

                    }
                    /// END
                }

                if(object->hasComponent<Timer>())
                {
                    Timer *timer = object->getComponent<Timer>();
                    timer->update(ms);
                    if(timer->timeIsUp())
                    {
                        if(object->hasComponent<Explosive>())
                        {
                            explosion(object, world);
                        }
                        object->deactivate();
                        //entityManager->removeRequest(object->getID());
                    }
                }
                if(object->hasComponent<Destroyer>() && !object->getComponent<Destroyer>()->isDone())
                {
                    object->getComponent<Destroyer>()->done();
                    if(world->getComponent<World>()->getCell(grid_coor.x, grid_coor.y)->getComponent<SquareCell>()->getType() == CELL_DIRT)
                    {
                        world->getComponent<World>()->destroyDirt(grid_coor.x, grid_coor.y, entityManager, _objectFactory); /// to nie powinno tak dzialac
                    }
                    else
                    {
                        //printf("looking for targets for %d\n", object->getID());
                        for(auto obj_m : entityManager->entity())
                        {
                            entity_ptr obj = obj_m.second;
                            if(obj->getID() == object->getID()) continue;
                            if((obj->hasComponent<PhysicalFormComponent>()) &&
                               (obj->getComponent<PhysicalFormComponent>()->getGridPos() == grid_coor) &&
                               (obj->getComponent<PhysicalFormComponent>()->isDestructible()))
                            {
                                        obj->deactivate();
                                       // entityManager->removeRequest(obj->getID());
                            }
                        }
                    }
                }
            }
        }

    }
}
/*
void ControllingSystem::collides(entity_ptr obj1, entity_ptr obj2, vector2d &normal)
{
    SDL_Rect r1 = obj1->getComponent<PhysicalFormComponent>()->rect(),
             r2 = obj2->getComponent<PhysicalFormComponent>()->rect(),
             intersection;
     if(SDL_IntersectRect(&r1,&r2,&intersection))
     {

     }
}
*/
void ControllingSystem::plantBomb(int x, int y, BombPlanter *bombPlanter, World *world)
{
    int range = bombPlanter->getRange();
    int_vector2d pos = int_vector2d(x,y);
    _objectFactory->createBomb(x, y, range);
    bombPlanter->plant();
    world->setUnsafe(x,y);
    //printf("%dx%d set as unsafe (%d)\n",x,y,(int)world->isSafe(x,y));
    bool av[4];
    for(int i=0;i<4;i++)
        av[i]=true;

    for(int i=1;i<=range;i++)
    {
        for(int j=0;j<4;j++) // kierunki
        {
            int x,y;
            if(j==0)x = pos.x, y = pos.y-i;
            if(j==1)x = pos.x, y = pos.y+i;
            if(j==2)x = pos.x-i, y = pos.y;
            if(j==3)x = pos.x+i, y = pos.y;
            entity_ptr cell = world->getCell(x,y);
            if(av[j] && cell && (cell->getComponent<SquareCell>()->getType() != CELL_WALL))
            {
                if(cell->getComponent<SquareCell>()->getType() == CELL_DIRT)
                    av[j] = false;
                world->setUnsafe(x,y);
            }
            else av[j] = false;
        }
    }
}
void ControllingSystem::explosion(entity_ptr bomb, entity_ptr world_entity)
{
    int_vector2d pos = bomb->getComponent<PhysicalFormComponent>()->getGridPos();
    World *world = world_entity->getComponent<World>();
    printf("BOOM at %dx%d\n",pos.x,pos.y);

    int range = bomb->getComponent<Explosive>()->getRange();

    bool av[4];
    for(int i=0;i<4;i++)
        av[i]=true;

    _objectFactory->createExplosion(pos.x,pos.y);
    world->setSafe(pos.x,pos.y);

    for(int i=1;i<=range;i++)
    {
        for(int j=0;j<4;j++) // kierunki
        {
            int x,y;
            if(j==0)x = pos.x, y = pos.y-i;
            if(j==1)x = pos.x, y = pos.y+i;
            if(j==2)x = pos.x-i, y = pos.y;
            if(j==3)x = pos.x+i, y = pos.y;
            entity_ptr cell = world->getCell(x,y);
            if(av[j] && cell && (cell->getComponent<SquareCell>()->getType() != CELL_WALL))
            {
                if(cell->getComponent<SquareCell>()->getType() == CELL_DIRT)
                    av[j] = false;
                _objectFactory->createExplosion(x,y);
                world->setSafe(x,y);
            }
            else av[j] = false;
        }
    }


}
bool ControllingSystem::itIsAGoodSpotToDropABomb(int x, int y, entity_ptr world_entity) // sprawdza tylko czy nie stoi przypadkiem obok dirta
{
    bool result = false;
    World *world = world_entity->getComponent<World>();
    int tx = x, ty = y;
    for(int i=0;i<4;i++)
    {
        if(i==0)tx = x - 1;
        if(i==1)tx = x + 1;
        if(i==2)tx = x, ty = y - 1;
        if(i==3)ty = y + 1;
        if(world->valid(tx,ty) && world->getCell(tx,ty)->getComponent<PhysicalFormComponent>()->isDestructible()) result = true;
    }
    return result;
}
void ControllingSystem::setRunaway(int x, int y, AIController *controller, World *world)
{
    Path path;
    pathFromTo(int_vector2d(x, y), int_vector2d(x, y), world, path);
    controller->setPath(path);
}

Path ControllingSystem::pathFromTo(int_vector2d from, int_vector2d to, World *world, Path &path) // jesli to==from szuka najblizszego bezpiecznego punktu
{
    /// BFS
//    Path path;
    printf("pathFromTo(%dx%d)\n",from.x,from.y);
    bool lookingForClosestSafe = (from == to);


    queue<int_vector2d> to_check;

    int w = world->width(),
        h = world->height();
	vector<vector<bool>> V;
	V.resize(h);

	vector<vector<int_vector2d>> previous;
	previous.resize(h);
	for(int i=0; i<h; i++)
    {
        previous[i].resize(w);
        V[i].resize(w,0);
        for(int j=0; j<w; j++)
            V[i][j] = false;
    }

    previous[from.y][from.x] = from;

	to_check.push(from);

	while(!to_check.empty())
	{
		int_vector2d current = to_check.front();
		to_check.pop();

		V[current.y][current.x] = true;

		printf("BFS at %dx%d\n",current.x,current.y);
		if(lookingForClosestSafe)
        {
            if(world->valid(current.x,current.y) && world->isSafe(current.x,current.y))
            {
                to = current;
                printf("found safe place at %dx%d\n",to.x,to.y);
                break;
            }
        }
        else if(current == to) break;

        for(int i=0; i<4; i++)
        {
            int_vector2d neighbour;
            if(i==0) neighbour.x = current.x, neighbour.y = current.y-1;
            if(i==1) neighbour.x = current.x, neighbour.y = current.y+1;
            if(i==2) neighbour.x = current.x-1, neighbour.y = current.y;
            if(i==3) neighbour.x = current.x+1, neighbour.y = current.y;
            //printf("checking neighbour %dx%d\n",neighbour.x,neighbour.y);
            if(world->valid(neighbour.x,neighbour.y))
            {
                if((V[neighbour.y][neighbour.x]==false) && (world->getCell(neighbour.x,neighbour.y)->getComponent<SquareCell>()->getType() == CELL_FLOOR))
                {
                    to_check.push(neighbour);
                    previous[neighbour.y][neighbour.x] = current;
                }
            }
        }
	}
	//printf("checked all neighbours\n");
	while(to!=from)
    {
        printf("+%dx%d ",to.x,to.y);
        path.push_front(to);
        to = previous[to.y][to.x];
    }
    printf("path found\n");
    return path;
}
