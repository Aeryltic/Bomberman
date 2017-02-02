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
    man->addComponent(new Alive);
    man->addComponent(new PhysicalFormComponent((x)*GRID_SIZE ,(y)*GRID_SIZE, 2, GRID_SIZE, GRID_SIZE, MAN_SPEED));
    man->getComponent<PhysicalFormComponent>()->setMovable();
    man->getComponent<PhysicalFormComponent>()->setDestructible(true);
    man->getComponent<PhysicalFormComponent>()->setSolid(true);
    man->getComponent<PhysicalFormComponent>()->setZ(2);
    man->addComponent(new MovementController);
    man->addComponent(new TextureComponent(_graphicsManager->getTexture(tex_path)));
    man->addComponent(new BombPlanter(INITIAL_BOMB_RANGE));
    return man;
}

entity_ptr ObjectFactory::createPlayer(int x, int y)
{
    printf("creating player at %d x %d\n", x, y);
    entity_ptr player = createMan(x, y, "textures/player.png");
    player->addComponent(new KeyboardController(_inputManager));
    player->addComponent(new Player);

    player->activate();
    printf("PLAYER READY (ID:%d)\n", player->getID());
    return player;
}

entity_ptr ObjectFactory::createEnemy(int x, int y)
{
    printf("creating enemy at %d x %d\n",x,y);
    entity_ptr enemy = createMan(x,y,"textures/enemy.png");
    enemy->addComponent(new AIController());
    enemy->addComponent(new Enemy);
    enemy->activate();
    printf("enemy ready\n");
    return enemy;
}

entity_ptr ObjectFactory::createBomb(int x, int y, unsigned range)
{
    printf("creating bomb at %d x %d\n",x,y);
    entity_ptr bomb = createDefault();
    bomb->addComponent(new PhysicalFormComponent((x)*GRID_SIZE ,(y)*GRID_SIZE, 1, GRID_SIZE, GRID_SIZE, MAN_SPEED));
    bomb->addComponent(new Timer(2000));
    bomb->addComponent(new TextureComponent(_graphicsManager->getTexture("textures/bomb.png")));
    bomb->addComponent(new Explosive(range));

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
    grid->getComponent<SquareCell>()->setType((WorldCellType)t);
    switch (t)
    {
        case CELL_FLOOR: // FLOOR
        {
            grid->addComponent(new TextureComponent(_graphicsManager->getTexture("textures/floor.png")));
            //grid->addComponent(new NavNode());
            grid->getComponent<SquareCell>()->unblock();
            grid->getComponent<SquareCell>()->setSafe();
            grid->getComponent<PhysicalFormComponent>()->setDestructible(false);
            break;
        }
        case CELL_WALL: // WALL
        {
            grid->addComponent(new TextureComponent(_graphicsManager->getTexture("textures/wall.png")));
            grid->getComponent<SquareCell>()->block();
            grid->getComponent<PhysicalFormComponent>()->setSolid(true);
            grid->getComponent<PhysicalFormComponent>()->setDestructible(false);
            break;
        }
        case CELL_DIRT: // DIRT
        {
            grid->addComponent(new TextureComponent(_graphicsManager->getTexture("textures/dirt.png")));
            grid->getComponent<SquareCell>()->block();
            grid->getComponent<PhysicalFormComponent>()->setSolid(true);
            grid->getComponent<PhysicalFormComponent>()->setDestructible(true);
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
                world->getComponent<World>()->addCell(createWorldCell(j,i,t));
            }
        }
//        world->getComponent<World>()->setup();
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
