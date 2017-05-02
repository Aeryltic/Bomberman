#ifndef COMPONENTS_H
#define COMPONENTS_H

//class SolidComponent : public Component /// uses PhysicalForm, sets collisions
//{
//    public:
//        SolidComponent() {}
//        virtual ~SolidComponent() {}
//    /// SYSTEM NEEDED
//};
//class KeyboardController : public Component
//{
//    public:
//        KeyboardController(InputManager *iManager) : Component() {_iManager = iManager;}
//        virtual ~KeyboardController() {}
//        void setTarget(entity_ptr target){_target = target; setActive();}
//        void setActive();
//
//        InputManager *getInputManager() {return _iManager;}
//    protected:
//       // void work(int ms);
//    private:
//        InputManager *_iManager;
//
//};
//class Alive : public Component /// to indicate that if dies should be removed or something - should be handled externally (using events or some system)
//{
//    public:
//        Alive() {_alive = true;_AliveCount++;}
//        virtual ~Alive() {_AliveCount--;}
//        //static int getCount(){return _count;}
//    private:
//        bool _alive;
//        int _type;
//
//       // static int _count;
//    /// SYSTEM NEEDED
//};
//
///*
//class MovementComponent : public Component /// uses PhysicalForm
//{
//    public:
//        MovementComponent() {_maxV = 50.0; _v = 0.0; _angle = 0.0; setActive();}
//        MovementComponent(double maxV) {_maxV = maxV; _v = 0.0; _angle = 0.0; setActive();}
//        virtual ~MovementComponent() {}
//        void work(int ms);
//
//
//    private:
//
//};
//*/
//class Dangerous : public Component /// enemies will flee away from tiles with this component
//{
//
//};
//
//class Timer : public Component
//{
//    public:
//        Timer(int timer) : Component(), _msLeft(timer) {}
//        ~Timer(){}
//        bool timeIsUp(){return _msLeft <= 0;}
//    protected:
//        void work(int ms) {_msLeft-=ms;}
//    private:
//        int _msLeft;
//};
///* // for later use
//class NavNode : public Component    /// uses PhysicalForm
//{
//    public:
//        NavNode() : Component() {}
//        ~NavNode() {}
//        vector2d coor();
//        NavNode *getNeighbour(int dir);
//        void setLink(int dir, NavNode *node);
//        // vector<NavNode *> v // neighbouring vertexes // not gut ajdija, to powinien zalatwiac system... chociaz moze...
//    unordered_map<int, NavNode*> _linked; // int = Direction (do nawigacji)
//};
//*/
//class SquareCell : public Component /// powinny byc przetwarzane jako instancje - za duza redundancja
//{
//    public:
//        SquareCell(WorldCellType type = CELL_NONE) : Component() {_type = type; _safe = true; _available = true;}
//        ~SquareCell() {}
//
//        void setType(WorldCellType type){_type = type;}
//        WorldCellType getType(){return _type;}
//
//        void block(){_available = false;}
//        void unblock(){_available = true;}
//        bool available(){return _available;}
//
//        bool isSafe() {return _safe;}
//       // void setDanger(bool danger) {_dangerous = danger;}
//        void setSafe(){_safe = true;}
//        void setUnsafe(){_safe = false;}
//
//    private:
//        WorldCellType _type;
//        bool _available;
//        bool _safe;
//};
//
//class World : public Component
//{
//    public:
//        World(int w, int h) : Component(), _w(w), _h(h) {_square.resize(_h); for(int i=0;i<_h;i++)_square[i].resize(_w);}
//        ~World() {}
//
//        void setup();
//        bool addCell(entity_ptr cell);//, int x, int y);
//        bool replace(entity_ptr cell);
//
//        bool valid(int x, int y){ return ((x>=0) && (x<_w) && (y>=0) && (y<_h));}
//        int_vector2d getNearestCellCoorFromGivenPosInGivenDirection(int_vector2d pos, int dir); /// need fixing
//
//        entity_ptr getCell(int x, int y){if(valid(x,y))return _square[y][x].lock(); return nullptr;}
//
//        bool isDangerous(int x, int y);
//
//        void destroyDirt(int x, int y, EntityManager *entityManager);
//
//        void setSafe(int x, int y);
//        void setUnsafe(int x, int y);
//        bool isSafe(int x, int y);
//        bool isSafe(int_vector2d p);
//
//        int width(){return _w;}
//        int height(){return _h;}
//
//        void blockCell(int x, int y);
//        void unblockCell(int x, int y);
//    private:
//        int _w, _h;
//        vector<vector<weak_ptr<Entity>>> _square;
//};
///*
//class PlayerControllerComponent : public Component /// uses PhysicalForm
//{
//    public:
//        PlayerControllerComponent(InputManager *iManager) : Component() {_iManager = iManager;}
//        virtual ~PlayerControllerComponent() {}
//        void setTarget(entity_ptr target){_target = target; setActive();}
//        void setActive();
//
//    protected:
//        void work(int ms);
//    private:
//        InputManager *_iManager;
//
//};
//*/
//
//class AIController : public Component
//{
//    public:
//        AIController() : Component() {}
//        ~AIController() {}
//        void setDir(int dir){_dir = dir;}
//        int getDir(){return _dir;}
//        void setPath(Path path){_path = path;}
//        bool hasPath(){return !_path.empty();}
//        void clearPath(){_path.clear();}
//        int_vector2d nextStop(){int_vector2d next = _path.front(); _path.pop_front();/* printf("nextStop()=%dx%d\n",next.x,next.y);*/return next;}
//        void print(){printf("path: ");for(auto p:_path)printf("%dx%d ",p.x,p.y);printf("\n");}
//    private:
//        int _dir;
//        Path _path;
//};
//
//class MovementController : public Component
//{
//    public:
//        MovementController() : Component() {_physicalForm = nullptr;}
//        ~MovementController() {}
//        void setTarget(entity_ptr target){/*printf("MovementController::setTarget()\n");*/_target = target; MovementController::setActive();}
//        //void setDest(NavNode *dest) { _dest = dest;} /// wrong
//        void setActive();
//
//        // when active ....
//        vector2d current();
//
//        void work(int ms);
//
//        void setDest(vector2d dest);// {_dest = dest;}
//        bool destReached();
//
//       // void setDest(int dir);
//
//
//
//   //     void setCurrent(NavNode *node){ _current = _dest = node;} /// wrong
//    private:
//
//        //NavNode *_dest; /// wrong
//        //NavNode *_current; /// wrong
//        vector2d _dest; /// ok
//        PhysicalForm *_physicalForm;
//
//        bool _readyToStop;
//        bool _reached;
//        bool _moving;
// //       bool _moving;
//};
///*
//class NPCControllerComponent : public Component /// uses PhysicalForm
//{
//    public:
//        NPCControllerComponent() : Component() {_hasDestination = false;}
//    protected:
//        void work(int ms);
//    private:
//        vector2d _dest;
//        bool _hasDestination;
//};
//*/
//
//
//class BombPlanter : public Component
//{
//    public:
//        BombPlanter(unsigned range) : Component() { _range = range; _toNextPlant=0;_active = true;}
//        ~BombPlanter() {}
//        bool canPlantNext() {return _toNextPlant<=0; }
//        void plant() {/*_lastPlant = SDL_GetTicks();*/ _toNextPlant = 3000;}
//        unsigned getRange(){return _range;}
//    protected:
//        void work(int ms){if(_toNextPlant>=0)_toNextPlant-=ms;}
//    private:
//
//        int _toNextPlant;
//        unsigned _range;
//};
//
//class Explosive : public Component
//{
//    public:
//        Explosive(int range) : Component(), _range(range) {}
//        ~Explosive() {}
//        int getRange() {return _range;}
//        void setRange(int range) {_range = range;}
//    private:
//        int _range;
//};
//
//class Destroyer : public Component
//{
//    public:
//        Destroyer() : Component() {_done = false;}
//        ~Destroyer() {}
//        void done(){_done = true;}
//        bool isDone(){return _done;}
//    private:
//        bool _done;
//};
//
//class Player : public Component
//{
//    public:
//        Player() : Component() {}
//        ~Player();
//    private:
//};
//
//class Enemy : public Component
//{
//    public:
//        Enemy() : Component() {_count++;}
//        ~Enemy();
//
//    private:
//        static int _count;
//};

#endif // COMPONENTS_H
