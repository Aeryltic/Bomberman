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
    for(auto object : entityManager->entity())
    {
        if(object->hasComponent<PhysicalFormComponent>())
        {
            PhysicalFormComponent *physicalForm = object->getComponent<PhysicalFormComponent>();
            physicalForm->update(ms);
            if(object->hasComponent<MovementController>())
            {
                MovementController *movementController = object->getComponent<MovementController>();
                movementController->update(ms);

                if(object->hasComponent<PlayerControllerComponent_v2>())
                {
                    PlayerControllerComponent_v2 *controller = object->getComponent<PlayerControllerComponent_v2>();
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
                                Vector2D pos = physicalForm->getGridPos();
                                objectFactory->createBomb(pos.x, pos.y);
                                bombPlanter->plant();
                            }
                        }
                    }

                }
                if(object->hasComponent<AIController>())
                {
                    if(movementController->destReached()) /// need to fix this
                    {
                        int dir = rand()%DIR_MAX;
                        movementController->setDest(world->getComponent<World>()->getNearestCellCoorFromGivenPosInGivenDirection(physicalForm->getPos(),dir));
                    }
                    if(object->hasComponent<BombPlanter>())
                    {
                        Vector2D pos = physicalForm->getGridPos();
                        if(itIsAGoodSpotToDropABomb(pos.x, pos.y, world))
                        {
                            BombPlanter *bombPlanter = object->getComponent<BombPlanter>();
                            if(bombPlanter->canPlantNext())
                            {
                                objectFactory->createBomb(pos.x, pos.y);
                                bombPlanter->plant();
                            }
                        }
                    }

                }
            }

            if(object->hasComponent<BombTimer>())
            {
                BombTimer *timer = object->getComponent<BombTimer>();
                timer->update(ms);
                if(timer->timeIsUp())
                {
                    Vector2D pos = physicalForm->getGridPos();
                    explosion(pos.x, pos.y);
                    entityManager->addToRemoveList(object->getID());
                }
            }
        }
    }
}
/*
void ControllingSystem::collides(entity_ptr obj1, entity_ptr obj2, Vector2D &normal)
{
    SDL_Rect r1 = obj1->getComponent<PhysicalFormComponent>()->rect(),
             r2 = obj2->getComponent<PhysicalFormComponent>()->rect(),
             intersection;
     if(SDL_IntersectRect(&r1,&r2,&intersection))
     {

     }
}
*/
void ControllingSystem::explosion(int x, int y)
{
    printf("BOOM at %dx%d\n",x,y);


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
Path ControllingSystem::pathFromTo(Vector2D from, Vector2D to) /// dodac mozliwosc wybierania czy szukac drog przez piach itd
{
    /// BFS
    Path path;
    /*
    Entity world = _entityManager->getWorld();


    queue<int> kolejka;

	bool V[n];
	for(int j=0;j<n;++j)V[j] = false;//Wierzcho³ki nie odwiedzone

	kolejka.push(szukany);//Wrzucamy startuj¹cy wierzcho³ek na kolejke

	while(!kolejka.empty())
	{
		pokaz_zawartosc_kolejki_i_odwiedzone(kolejka);//Do symulacji


		szukany = kolejka.front();
		kolejka.pop();//Usuwamy odwiedzany element

		printf("\n\nOdwiedzam: %d\n",szukany);

		VODWIEDZONE.push(szukany);//Do symulacji odwiedzonych

		V[szukany] = true;//ODwiedziliœmy ju¿ ten

		for(int j = 0;j < n;++j)
		{
			if(G[j][szukany] != 0 && V[j] == false)
			{
				kolejka.push(j);//Wrzucamy na stos jego s¹siadów
				V[j] = true;//Znaznaczamy ,¿e go odwiedzimy!(w niedalekiej przysz³oœci)
				//Inaczej bêdziemy mieli np tak¹ sytuacjê w stosie 2,3,4,2 <-- 2x dwójka
			}
		}
	}
*/
    return path;
}

