#include "Noble.h"
#include "Warrior.h"
using namespace std;

namespace WarriorCraft {
    // constructor
    Warrior::Warrior(const std::string& name, double strength) 
        : name(name), strength(strength), employed(false) {}

    // getter for name
    const std::string& Warrior::get_name() const {
        return name;
    }

    // getter for strength
    const double Warrior::get_strength() const {
        return strength;
    }

    // change strength during battle
    void Warrior::change_strength(double new_strength) {
        strength = new_strength;
    }

    // getter for employed
    const bool Warrior::isHired() const {
        return employed;
    }

    // changes employed to true when hired, sets employer
    void Warrior::change_employment_to_hired(bool status, Noble& new_boss) {
        employed = status;
        employer = &new_boss;
    }

    // changes employment to false when fired
    void Warrior::change_employment_to_fired(bool status) {
        employed = false;
        employer = nullptr;
    }

    // Warrior no longer employed, tells employer
    void Warrior::runaway() {
        employer->loses_warrior(*this);
        std::cout << name << " flees in terror, abandoning his lord, " << 
        employer->get_name() << std::endl;
        employed = false;
        employer = nullptr;
    }

    // output operator for Warrior
    std::ostream& operator<<(std::ostream& os, const Warrior& warrior) {
        os << warrior.name << ": " << warrior.strength << std::endl;
        return os;
    }
}