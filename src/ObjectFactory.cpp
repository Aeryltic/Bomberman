#include "ObjectFactory.h"
#include <fstream>
#include "Constants.h"
#include "Entity.h"

ObjectFactory::~ObjectFactory()
{
    printf("delete ObjectFactory\n");
}

entity_ptr ObjectFactory::createDefault()
{
    entity_ptr def = make_shared<Entity>();
    _entityManager->addEntity(def);
    //_entity.push_back(def);
    return def;
}

entity_ptr ObjectFactory::createMan(int x, int y)
{
    entity_ptr man = createDefault();
    man->addComponent(new LifeComponent);
    man->addComponent(new PhysicalFormComponent((x)*GRID_SIZE ,(y)*GRID_SIZE, GRID_SIZE, GRID_SIZE, MAN_SPEED));
    man->getComponent<PhysicalFormComponent>()->setMovable();
    man->getComponent<PhysicalFormComponent>()->setSolid(true);
    man->getComponent<PhysicalFormComponent>()->setZ(1);
    return man;
}

entity_ptr ObjectFactory::createPlayer(int x, int y)
{
    printf("creating player at %d x %d\n",x,y);
    entity_ptr player = createMan(x,y);
    player->addComponent(new PlayerControllerComponent(_inputManager));
    player->addComponent(new TextureComponent(_graphicsManager->getTexture("textures/player.png")));

    player->setAsTarget();
    printf("player ready\n");
    return player;
}

entity_ptr ObjectFactory::createEnemy(int x, int y)
{
    printf("creating enemy at %d x %d\n",x,y);
    entity_ptr enemy = createMan(x,y);
    enemy->addComponent(new NPCControllerComponent());
    enemy->addComponent(new TextureComponent(_graphicsManager->getTexture("textures/enemy.png")));
    return enemy;
}

entity_ptr ObjectFactory::createBomb(int x, int y)
{
    printf("creating bomb at %d x %d\n",x,y);
    entity_ptr bomb = createDefault();
    /// bomb components
    return bomb;
}

entity_ptr ObjectFactory::createWorldGrid(int x, int y, int t)
{
    entity_ptr grid = make_shared<Entity>();
    grid->addComponent(new PhysicalFormComponent(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE, 0));
    grid->getComponent<PhysicalFormComponent>()->setStatic();

    switch (t)
    {
        case 0: // FLOOR
        {
            grid->addComponent(new TextureComponent(_graphicsManager->getTexture("textures/floor.png")));
            grid->addComponent(new NavNode()); // do kierowania botami
            break;
        }
        case 1: // WALL
        {
            grid->addComponent(new TextureComponent(_graphicsManager->getTexture("textures/wall.png")));
            grid->getComponent<PhysicalFormComponent>()->setSolid(true);
            break;
        }
        case 2: // DIRT
        {
            grid->addComponent(new TextureComponent(_graphicsManager->getTexture("textures/dirt.png")));
            grid->getComponent<PhysicalFormComponent>()->setSolid(true);
            grid->getComponent<PhysicalFormComponent>()->setDestructible(true);
            break;
        }
    }
    return grid;
}

bool ObjectFactory::createWorld(string path) /// OBSLUGA BLEDOW, BLAGAM !!!
{
    printf("INFO: Loading world.\n");
    ifstream file;
    file.open(path);
    if(file.good())
    {
        vector<entity_ptr> entity_buffer;
        int w,h;
        file>>w>>h;
        for(int i=0; i<h; i++)
        {
            for(int j=0; j<w; j++)
            {
                int t;
                file>>t;
                entity_buffer.push_back(createWorldGrid(j,i,t));
            }
        }
        int xp, yp;
        file>>xp>>yp;
        entity_buffer.push_back(createPlayer(xp,yp));
        int e;
        file>>e;
        while(e--)
        {
            int xe,ye;
            if(file>>xe>>ye)
                entity_buffer.push_back(createEnemy(xe,ye));
            else printf("WOOHOOO - need to fix that file!!!\n");
        }
        for(auto e: entity_buffer)
        {
            _entityManager->addEntity(e);
        }
        file.close();
        printf("INFO: World loaded successfully.\n");
        return 1;
    }
    printf("ERROR: Wrong world path.\n");
    return 0;
}
