#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {
    class Noble;

    class Warrior {
        private:
            std::string name;
            double strength;
            bool employed;
            Noble* employer;

            friend std::ostream& operator<<(std::ostream& os, const Warrior& warrior);

        public:
            Warrior(const std::string& name, double strength);
            const std::string& get_name() const;
            const double get_strength() const;
            void change_strength(double new_strength);
            const bool isHired() const;
            void change_employment_to_hired(bool status, Noble& new_boss);
            void change_employment_to_fired(bool status);
            void runaway();
    };
}

#endif