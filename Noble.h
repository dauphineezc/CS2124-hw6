#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {
    class Warrior;

    class Noble {
    private:
        std::string name;
        bool dead;
        std::vector<Warrior*> army;

        friend std::ostream& operator<<(std::ostream& os, const Noble& noble);

    public:
        Noble(const std::string& name);
        const std::string& get_name() const;
        const bool get_life_status() const;
        bool hire(Warrior& warrior);
        bool fire(Warrior& warrior);
        void loses_warrior(Warrior& runaway);
        const double army_strength();
        void battle(Noble& opponent);
        void i_lose(Noble& opponent, double reduce_by);
        void opponent_loses(Noble& opponent, double reduce_by);
        void same_strength(Noble& opponent);
    };
}

#endif