#include "ControllingSystem.h"

#include "InputManager.h"

ControllingSystem::ControllingSystem()
{
    //ctor
}

ControllingSystem::~ControllingSystem()
{
    //dtor
}

void ControllingSystem::update(EntityManager *entityManager, ObjectFactory *objectFactory, int ms)
{
    entity_ptr world = entityManager->getWorld();
    entity_ptr player = entityManager->getPlayer();
    //printf("player.count() = %ld\n",player.use_count());
    for(auto object_m : entityManager->entity())
    {
        entity_ptr object = object_m.second;
       // if(object->isActive())
        {
            if(object->hasComponent<PhysicalFormComponent>())
            {
                PhysicalFormComponent *physicalForm = object->getComponent<PhysicalFormComponent>();
                int_vector2d grid_coor = physicalForm->getGridPos();
                physicalForm->update(ms);
                if(object->hasComponent<MovementController>())
                {
                    MovementController *movementController = object->getComponent<MovementController>();
                    movementController->update(ms);

                    if(object->hasComponent<KeyboardController>())
                    {
                        KeyboardController *controller = object->getComponent<KeyboardController>();
                        InputManager *_iManager = controller->getInputManager();
                       // physicalForm->update(ms);
                        Direction dir = DIR_NONE;
                        if(_iManager->keyStatus(SDLK_w) & (KEY_PRESSED|KEY_DOWN))   // go up
                        {
                            dir = DIR_UP;
                          //  printf("going up\n");
                        }
                        else if(_iManager->keyStatus(SDLK_s) & (KEY_PRESSED|KEY_DOWN))  // go down
                        {
                            dir = DIR_DOWN;
                         //   printf("going down\n");
                        }
                        if(_iManager->keyStatus(SDLK_a) & (KEY_PRESSED|KEY_DOWN))  // go left
                        {
                            dir = DIR_LEFT;
                          //  printf("going left\n");
                        }
                        else if(_iManager->keyStatus(SDLK_d) & (KEY_PRESSED|KEY_DOWN))  // go right
                        {
                            dir = DIR_RIGHT;
                         //   printf("going right\n");
                        }

                        if(dir)
                        {
                            movementController->setDest(world->getComponent<World>()->getNearestCellCoorFromGivenPosInGivenDirection(physicalForm->getPos(),dir));
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
                                    objectFactory->createBomb(grid_coor.x, grid_coor.y);
                                    bombPlanter->plant();
                                }
                            }
                        }

                    }
                    /// AIController BEGIN
                    if(object->hasComponent<AIController>()) /// nie zamykac w klatce 1x1
                    {
                        /// need cleverer AI
                        AIController *controller = object->getComponent<AIController>();
                        if(movementController->destReached())
                        {
                            //int_vector2d curr_pos
                            int dir = controller->getDir();
                            vector2d curr_pos = physicalForm->getPos();
                            vector<int>possible;
                            //bool possible[DIR_MAX] = {false};
                            for(int i=1; i<DIR_MAX; i++) // sprawdzanie gdzie mozna sie ruszyc
                            {
                                if(curr_pos!=world->getComponent<World>()->getNearestCellCoorFromGivenPosInGivenDirection(physicalForm->getPos(),i))possible.push_back(i);
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
                                for(unsigned i=0; i<possible.size(); i++) // wolimy nie cofac (chociaz i tak to nie dziala)
                                {
                                    if(possible[i] == opposite)
                                    {
                                        possible.erase(possible.begin() + i);
                                        break;
                                    }
                                }
                                dir = possible[rand()%possible.size()];
                            }
                            vector2d new_dest = world->getComponent<World>()->getNearestCellCoorFromGivenPosInGivenDirection(physicalForm->getPos(),dir);
                            controller->setDir(dir);
                            movementController->setDest(new_dest);
                        }
                        if(object->hasComponent<BombPlanter>())
                        {
                            if(itIsAGoodSpotToDropABomb(grid_coor.x, grid_coor.y, world))
                            {
                                BombPlanter *bombPlanter = object->getComponent<BombPlanter>();
                                if(bombPlanter->canPlantNext()) /* plant a bomb  */
                                {
                                    objectFactory->createBomb(grid_coor.x, grid_coor.y);
                                    bombPlanter->plant();
                                }
                            }
                        }
                    }
                    /// AIController END
                }

                if(object->hasComponent<Timer>())
                {
                    Timer *timer = object->getComponent<Timer>();
                    timer->update(ms);
                    if(timer->timeIsUp())
                    {
                        if(object->hasComponent<Explosive>())
                        {
                            explosion(object, world, objectFactory);
                        }
                        object->deactivate();
                    }
                }
                if(object->hasComponent<Destroyer>() && !object->getComponent<Destroyer>()->isDone())
                {
                    object->getComponent<Destroyer>()->done();
                    if(world->getComponent<World>()->getCell(grid_coor.x, grid_coor.y)->getComponent<SquareCell>()->getType() == CELL_DIRT)
                    {
                        world->getComponent<World>()->destroyDirt(grid_coor.x, grid_coor.y, entityManager, objectFactory);
                    }
                    else
                    {
                        //printf("looking for targets for %d\n", object->getID());
                        for(auto obj_m : entityManager->entity())
                        {
                            entity_ptr obj = obj_m.second;
                            if(obj->getID() == object->getID()) continue;
                            if(obj->hasComponent<PhysicalFormComponent>())
                            {
                                if(obj->getComponent<PhysicalFormComponent>()->getGridPos() == grid_coor)
                                {
                                    if(obj->getComponent<PhysicalFormComponent>()->isDestructible())
                                    {
                                        //printf("DESTRUCTION: %d destroys %d\n", object->getID(), obj->getID());
                                        obj->deactivate();
                                    }
                                }
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
void ControllingSystem::explosion(entity_ptr bomb, entity_ptr world_entity, ObjectFactory *objectFactory)
{
    int_vector2d pos = bomb->getComponent<PhysicalFormComponent>()->getGridPos();
    World *world = world_entity->getComponent<World>();
    printf("BOOM at %dx%d\n",pos.x,pos.y);
    objectFactory->createExplosion(pos.x,pos.y);
    int range = bomb->getComponent<Explosive>()->getRange();
    bool up, down, left, right;
    up = down = left = right = true;
    for(int i=1; i<=range; i++)
    {
        entity_ptr cell = world->getCell(pos.x,pos.y-i);
        if(up && cell && cell->getComponent<SquareCell>()->getType() != CELL_WALL)
        {
            if(cell->getComponent<SquareCell>()->getType() == CELL_DIRT)
                up = false;
            objectFactory->createExplosion(pos.x,pos.y-i);
        }
        else up = false;

        cell = world->getCell(pos.x,pos.y+i);
        if(down && cell && cell->getComponent<SquareCell>()->getType()!=CELL_WALL)
        {
            if(cell->getComponent<SquareCell>()->getType() == CELL_DIRT)
                down = false;
            objectFactory->createExplosion(pos.x,pos.y+i);
        }
        else down = false;

        cell = world->getCell(pos.x-i,pos.y);
        if(left && cell && world->getCell(pos.x-i,pos.y)->getComponent<SquareCell>()->getType()!=CELL_WALL)
        {
            if(cell->getComponent<SquareCell>()->getType() == CELL_DIRT)
                left = false;
            objectFactory->createExplosion(pos.x-i,pos.y);
        }
        else left = false;

        cell = world->getCell(pos.x+i,pos.y);
        if(right && cell && world->getCell(pos.x+i,pos.y)->getComponent<SquareCell>()->getType()!=CELL_WALL)
        {
            if(cell->getComponent<SquareCell>()->getType() == CELL_DIRT)
                right = false;
            objectFactory->createExplosion(pos.x+i,pos.y);
        }
        else right = false;
    }
    // to up

}
bool ControllingSystem::itIsAGoodSpotToDropABomb(int x, int y, entity_ptr world_entity) // sprawdza tylko czy nie stoi przypadkiem obok dirta
{
    bool result = false;
    World *world = world_entity->getComponent<World>();
    int tx = x, ty = y;
    tx = x - 1;
    if(world->valid(tx,ty) && world->getCell(tx,ty)->getComponent<PhysicalFormComponent>()->isDestructible()) result = true;
    tx = x + 1;
    if(world->valid(tx,ty) && world->getCell(tx,ty)->getComponent<PhysicalFormComponent>()->isDestructible()) result = true;
    tx = x;
    ty = y - 1;
    if(world->valid(tx,ty) && world->getCell(tx,ty)->getComponent<PhysicalFormComponent>()->isDestructible()) result = true;
    ty = y + 1;
    if(world->valid(tx,ty) && world->getCell(tx,ty)->getComponent<PhysicalFormComponent>()->isDestructible()) result = true;
    return result;
}
Path ControllingSystem::pathFromTo(vector2d from, vector2d to) /// dodac mozliwosc wybierania czy szukac drog na przelaj czy cus w ten desen
{
    /// BFS
    Path path;
    /*
    Entity world = _entityManager->getWorld();


    queue<int> kolejka;

	bool V[n];
	for(int j=0;j<n;++j)V[j] = false;//Wierzcho�ki nie odwiedzone

	kolejka.push(szukany);//Wrzucamy startuj�cy wierzcho�ek na kolejke

	while(!kolejka.empty())
	{
		pokaz_zawartosc_kolejki_i_odwiedzone(kolejka);//Do symulacji


		szukany = kolejka.front();
		kolejka.pop();//Usuwamy odwiedzany element

		printf("\n\nOdwiedzam: %d\n",szukany);

		VODWIEDZONE.push(szukany);//Do symulacji odwiedzonych

		V[szukany] = true;//ODwiedzili�my ju� ten

		for(int j = 0;j < n;++j)
		{
			if(G[j][szukany] != 0 && V[j] == false)
			{
				kolejka.push(j);//Wrzucamy na stos jego s�siad�w
				V[j] = true;//Znaznaczamy ,�e go odwiedzimy!(w niedalekiej przysz�o�ci)
				//Inaczej b�dziemy mieli np tak� sytuacj� w stosie 2,3,4,2 <-- 2x dw�jka
			}
		}
	}
*/
    return path;
}

void plantBomb(int x, int y, BombPlanter *planter)
{

}
