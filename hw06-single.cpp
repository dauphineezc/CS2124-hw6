// Zoe Dauphinee, hw06, Warriors and Nobles with cyclic association

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Noble;

class Warrior {
    private:
        string name;
        double strength;
        bool employed;
        Noble* employer;

        friend ostream& operator<<(ostream& os, const Warrior& warrior);

    public:
        Warrior(const string& name, double strength);
        const string& get_name() const;
        const double get_strength() const;
        void change_strength(double new_strength);
        const bool isHired() const;
        void change_employment_to_hired(bool status, Noble& new_boss);
        void change_employment_to_fired(bool status);
        void runaway();
};

class Noble {
    private:
        string name;
        bool dead;
        vector<Warrior*> army;

        friend ostream& operator<<(ostream& os, const Noble& noble);

    public:
        Noble(const string& name);
        const string& get_name() const;
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


// creates vectors, Nobles, and Warriors, calls status and battle
int main() {
    Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 4);
	Warrior sky("Leia", 6);
	Warrior wizard("Merlin", 9);
	Warrior jaffa("Teal'c", 9);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(jaffa);
	art.hire(cheetah);
	art.hire(wizard);
	art.hire(sky);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(nimoy);

	cout << "================ Initial Status ===============" << endl;
	cout << art << endl
	     << lance << endl
	     << jim << endl
	     << linus << endl
	     << billie << endl;
	cout << "===============================================\n\n";

	art.fire(cheetah);
	wizard.runaway();
	cout << endl << art << endl;

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);

	cout << "\n================ Final Status ===============" << endl;
	cout << art << endl
	     << lance << endl
	     << jim << endl
	     << linus << endl
	     << billie << endl;

	// Tarzan and Merlin should be unemployed
	cout << "Tarzan's Hire Status: " << boolalpha 
	     << cheetah.isHired() << endl;
	cout << "Merlin's Hire Status: " << boolalpha 
	     << wizard.isHired() << endl;
	cout << "===============================================\n\n";
}



/* 
methods for Warrior
*/

// constructor
Warrior::Warrior(const string& name, double strength) 
    : name(name), strength(strength), employed(false) {}

// getter for name
const string& Warrior::get_name() const {
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
    cout << name << " flees in terror, abandoning his lord, " << 
    employer->get_name() << endl;
    employed = false;
    employer = nullptr;
}

// output operator for Warrior
ostream& operator<<(ostream& os, const Warrior& warrior) {
    os << warrior.name << ": " << warrior.strength << endl;
    return os;
}


/* 
methods for Noble
*/

// constructor
Noble::Noble(const string& name) 
    : name(name), dead(false), army(0) {}

// getter for name
const string& Noble::get_name() const {
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
            cout << name << " failed to hire " << warrior.get_name() << endl;
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
    cout << name << " failed to hire " << warrior.get_name() << endl;
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
                cout << warrior.get_name() << ", you don't work for me any more! -- ";
                cout << name << "." << endl;
                for (size_t index2 = index; index2 < army.size(); ++index2) {
                    army[index2] = army[index2 + 1];
                }
                army.pop_back();
                return true;
            }
        }
        // Warrior isn't in Noble's army
        cout << name << " failed to fire " << warrior.get_name() << endl;
            return false;
    }
    // Noble doesn't exist
    if (dead) {
        cout << "failed to fire - Noble " << name << " doesn't exist!\n";
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
    cout << endl << name << " battles " << opponent.name << endl;
    double my_strength = army_strength();
    double opp_strength = opponent.army_strength();

    // both dead
    if (dead && opponent.dead) {
        cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        return;
    }
    // i'm dead
    else if (dead) {
        cout << "He's dead, " << opponent.name << endl;
        return;
    }
    // opponent is dead
    else if (opponent.dead) {
        cout << "He's dead, " << name << endl;
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
    cout << opponent.name << " defeats " << name << endl;
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
    cout << name << " defeats " << opponent.name << endl;
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
    cout << "Mutual Annihilation: ";
    cout << name << " and " << opponent.name << " die at each other's hands\n";
}

// output operator for Noble
ostream& operator<<(ostream& os, const Noble& noble) {
    os << noble.name << " has an army of " << noble.army.size() << endl;
    for (size_t index = 0; index < noble.army.size(); ++index) {
        os << "    " << *noble.army[index];
    }
    return os;
}