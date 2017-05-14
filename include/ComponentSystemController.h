#ifndef COMPONENTSYSTEMCONTROLLER_H
#define COMPONENTSYSTEMCONTROLLER_H
/*
#include <unordered_map>
#include <functional>
using namespace std;

using UpdateFunction = function<void(int)>;
/// DO WYWALENIA
class ComponentSystemController
{
    public:
        ComponentSystemController();
        virtual ~ComponentSystemController();

        static ComponentSystemController *getInstance()
        {
            static ComponentSystemController instance;
            return &instance;
        }
        unsigned registerUpdateFunction(UpdateFunction const &updateFun)
        {
            unsigned id = nextID();
            updateFunctions[id] = updateFun;
            return id;
        }
        void update(int ms);
        unsigned nextID()
        {
            static unsigned id = 0;
            return id++;
        }
    protected:

    private:
        unordered_map<unsigned, UpdateFunction> updateFunctions;

};
*/
#endif // COMPONENTSYSTEMCONTROLLER_H
