#include "Noble.h"
#include "Warrior.h"
using namespace std;

namespace WarriorCraft {
    // constructor
    Noble::Noble(const std::string& name) 
        : name(name), dead(false), army(0) {}

    // getter for name
    const std::string& Noble::get_name() const {
        return name;
    }
            
    // getter for dead/alive
    const bool Noble::get_life_status() const {
        return dead;
    }

    // hire a Warrior
    bool Noble::hire(Warrior& warrior) {
        if (!dead) {
            // if Noble is not dead, check to see if Warrior is already employed
            // Warrior is employed
            if (warrior.isHired()) {
                std::cout << name << " failed to hire " << warrior.get_name() << std::endl;
                return false;
            }
            // Warrior is unemployed
            else {
                army.push_back(&warrior);
                warrior.change_employment_to_hired(true, *this);
                return true;
            }
        }
        // Warrior is dead (fail)
        std::cout << name << " failed to hire " << warrior.get_name() << std::endl;
        return false;
    }

    // fire a Warrior
    bool Noble::fire(Warrior& warrior) {
        if (!dead) {
            // if Noble is not dead, check to see if Warrior is in Noble's army
            for (size_t index = 0; index < army.size(); ++index) {
                // Warrior found, go through with termination
                if (army[index] == &warrior) {
                    warrior.change_employment_to_fired(false);
                    std::cout << warrior.get_name() << ", you don't work for me any more! -- ";
                    std::cout << name << "." << std::endl;
                    for (size_t index2 = index; index2 < army.size(); ++index2) {
                        army[index2] = army[index2 + 1];
                    }
                    army.pop_back();
                    return true;
                }
            }
            // Warrior isn't in Noble's army
            std::cout << name << " failed to fire " << warrior.get_name() << std::endl;
                return false;
        }
        // Noble doesn't exist
        if (dead) {
            std::cout << "failed to fire - Noble " << name << " doesn't exist!\n";
        }
        return false;
    }

    // Warrior ran away
    void Noble::loses_warrior(Warrior& runaway) {
        for (size_t index = 0; index < army.size(); ++index) {
            if (army[index] == &runaway) {
                for (size_t index2 = index; index2 < army.size(); ++index2) {
                        army[index2] = army[index2 + 1];
                    }
                    army.pop_back();
            }
        }
    }

    // calculate strength of a Noble's army
    const double Noble::army_strength() {
        double strength = 0;
        for (size_t index = 0; index < army.size(); ++index) {
            strength += army[index]->get_strength();
        }
        return strength;
    }

    // two Nobles battle, outcome based on army strengths
    void Noble::battle(Noble& opponent) {
        std::cout << std::endl << name << " battles " << opponent.name << std::endl;
        double my_strength = army_strength();
        double opp_strength = opponent.army_strength();

        // both dead
        if (dead && opponent.dead) {
            std::cout << "Oh, NO!  They're both dead!  Yuck!" << std::endl;
            return;
        }
        // i'm dead
        else if (dead) {
            std::cout << "He's dead, " << opponent.name << std::endl;
            return;
        }
        // opponent is dead
        else if (opponent.dead) {
            std::cout << "He's dead, " << name << std::endl;
            return;
        }
        // i'm stronger than opponent
        if (my_strength > opp_strength) {
            double reduce_by = (opp_strength/my_strength);
            opponent_loses(opponent, reduce_by);
        }
        // opponent is stronger than me
        else if (opp_strength > my_strength) {
            double reduce_by = (my_strength/opp_strength);
            i_lose(opponent, reduce_by);
        }
        // equal strength
        else if (my_strength == opp_strength) {
            same_strength(opponent);
        }
    }

    // Noble and army die
    void Noble::i_lose(Noble& opponent, double reduce_by) {
        // opponent's army's strength gets reduced
        for (size_t index = 0; index < opponent.army.size(); ++index) {
            double new_strength = opponent.army[index]->get_strength() * (1-reduce_by);
            opponent.army[index]->change_strength(new_strength);
        }
        // my army's strength gets set to 0
        for (size_t index = 0; index < army.size(); ++index) {
            army[index]->change_strength(0);
        }
        // i'm now dead
        dead = true;
        std::cout << opponent.name << " defeats " << name << std::endl;
    }

    // opponent Noble and army die
    void Noble::opponent_loses(Noble& opponent, double reduce_by) {
        // my army's strength gets reduced
        for (size_t index = 0; index < army.size(); ++index) {
            double new_strength = army[index]->get_strength() * (1-reduce_by);
            army[index]->change_strength(new_strength);
        }
        // opponent's army's strength gets set to 0
        for (size_t index = 0; index < opponent.army.size(); ++index) {
            opponent.army[index]->change_strength(0);
        }
        // opponent is now dead
        opponent.dead = true;
        std::cout << name << " defeats " << opponent.name << std::endl;
    }

    // both Nobles and their armies die
    void Noble::same_strength(Noble& opponent) {
        for (size_t index = 0; index < army.size(); ++index) {
            army[index]->change_strength(0);
        }
        for (size_t index = 0; index < opponent.army.size(); ++index) {
            opponent.army[index]->change_strength(0);
        }
        dead = true;
        opponent.dead = true;
        std::cout << "Mutual Annihilation: ";
        std::cout << name << " and " << opponent.name << " die at each other's hands\n";
    }

    // output operator for Noble
    std::ostream& operator<<(std::ostream& os, const Noble& noble) {
        os << noble.name << " has an army of " << noble.army.size() << std::endl;
        for (size_t index = 0; index < noble.army.size(); ++index) {
            os << "    " << *noble.army[index];
        }
        return os;
    }
}