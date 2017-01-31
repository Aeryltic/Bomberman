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
    _entityManager->addRequest(def);
    //_entity.push_back(def);
    return def;
}

entity_ptr ObjectFactory::createMan(int x, int y, string tex_path)
{
    entity_ptr man = createDefault();
    man->addComponent(new LifeComponent);
    man->addComponent(new PhysicalFormComponent((x)*GRID_SIZE ,(y)*GRID_SIZE, 2, GRID_SIZE, GRID_SIZE, MAN_SPEED));
    man->getComponent<PhysicalFormComponent>()->setMovable();
    man->getComponent<PhysicalFormComponent>()->setSolid(true);
    man->getComponent<PhysicalFormComponent>()->setZ(2);
    man->addComponent(new MovementController);
    man->addComponent(new TextureComponent(_graphicsManager->getTexture(tex_path)));
    man->addComponent(new BombPlanter);
    return man;
}

entity_ptr ObjectFactory::createPlayer(int x, int y)
{
    printf("creating player at %d x %d\n",x,y);
    entity_ptr player = createMan(x,y,"textures/player.png");
    //player->addComponent(new PlayerControllerComponent(_inputManager));
    player->addComponent(new PlayerControllerComponent_v2(_inputManager));

    player->activate();
    printf("player ready\n");
    return player;
}

entity_ptr ObjectFactory::createEnemy(int x, int y)
{
    printf("creating enemy at %d x %d\n",x,y);
    entity_ptr enemy = createMan(x,y,"textures/enemy.png");
    enemy->addComponent(new AIController());

    enemy->activate();
    printf("enemy ready\n");
    return enemy;
}

entity_ptr ObjectFactory::createBomb(int x, int y)
{
    printf("creating bomb at %d x %d\n",x,y);
    entity_ptr bomb = createDefault();
    bomb->addComponent(new PhysicalFormComponent((x)*GRID_SIZE ,(y)*GRID_SIZE, 1, GRID_SIZE, GRID_SIZE, MAN_SPEED));
    bomb->addComponent(new Timer(2000));
    bomb->addComponent(new TextureComponent(_graphicsManager->getTexture("textures/bomb.png")));
    bomb->addComponent(new Explosive(4));

    bomb->getComponent<PhysicalFormComponent>()->setZ(1);
    bomb->activate();
    /// bomb components
    return bomb;
}

entity_ptr ObjectFactory::createWorldCell(int x, int y, int t)
{
    entity_ptr grid = createDefault();
    grid->addComponent(new PhysicalFormComponent(x * GRID_SIZE, y * GRID_SIZE, 0, GRID_SIZE, GRID_SIZE, 0));
    grid->getComponent<PhysicalFormComponent>()->setStatic();

    grid->addComponent(new SquareCell);
    switch (t)
    {
        case 0: // FLOOR
        {
            grid->addComponent(new TextureComponent(_graphicsManager->getTexture("textures/floor.png")));
            grid->addComponent(new NavNode()); // do kierowania botami
            grid->getComponent<SquareCell>()->setType(CELL_FLOOR);
            break;
        }
        case 1: // WALL
        {
            grid->addComponent(new TextureComponent(_graphicsManager->getTexture("textures/wall.png")));
            grid->getComponent<PhysicalFormComponent>()->setSolid(true);
            grid->getComponent<SquareCell>()->setType(CELL_WALL);
            break;
        }
        case 2: // DIRT
        {
            grid->addComponent(new TextureComponent(_graphicsManager->getTexture("textures/dirt.png")));
            grid->getComponent<PhysicalFormComponent>()->setSolid(true);
            grid->getComponent<PhysicalFormComponent>()->setDestructible(true);
            grid->getComponent<SquareCell>()->setType(CELL_DIRT);
            break;
        }
    }
    grid->activate();
    return grid;
}

entity_ptr ObjectFactory::createExplosion(int x, int y)
{
    entity_ptr expl = createDefault();
    expl->addComponent(new PhysicalFormComponent(x*GRID_SIZE,y*GRID_SIZE,3,GRID_SIZE,GRID_SIZE,0,0));
    expl->addComponent(new TextureComponent(_graphicsManager->getTexture("textures/explosion.png")));
    expl->addComponent(new Timer(1000));
    expl->addComponent(new Destroyer);
    return expl;
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

        entity_ptr world = make_shared<Entity>();
        world->addComponent(new World(w,h));
        world->activate();
        entity_buffer.push_back(world);

        for(int i=0; i<h; i++)
        {
            for(int j=0; j<w; j++)
            {
                int t;
                file>>t;
                //entity_buffer.push_back();
                world->getComponent<World>()->addCell(createWorldCell(j,i,t),j,i);
            }
        }
        world->getComponent<World>()->setup();
        int xp, yp;
        file>>xp>>yp;
        entity_buffer.push_back(createPlayer(xp,yp));
        //entity_buffer.back()->getComponent<MovementController>()->setCurrent(world->getComponent<World>()->getNavNode(xp,yp));
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
            _entityManager->addRequest(e);
        }
        file.close();
        printf("INFO: World loaded successfully.\n");
        return 1;
    }
    printf("ERROR: Wrong world path.\n");
    return 0;
}
