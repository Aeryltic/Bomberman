#ifndef AIPACKAGE_H
#define AIPACKAGE_H

#include <vector>
#include <string>

class AIPackage
{
    using Goal = std::pair<int, std::pair<std::string, bool>>;
    public:
        const std::string name;

        explicit AIPackage(std::string name); // nie ma żadnego bezargumentowego i być nie będzie
        virtual ~AIPackage();

        void add_action(std::string action);
        void add_goal(std::string goal_name, bool state, int priority);

        const std::vector<Goal>& get_goals() const {return goals;}
        const std::vector<std::string>& get_actions() const {return actions;}

    protected:

    private:
        std::vector<Goal> goals;
        std::vector<std::string> actions;
};

#endif // AIPACKAGE_H
