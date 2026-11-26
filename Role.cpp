#include "Role.hpp"

#include <algorithm>
#include <iostream>

namespace final {
int Base::aliveNumber = 0;

Base::Base(const std::string& name, int health, int attack)
    : name(name), health(health), attack(attack), alive(true), defensive(false) {
    ++aliveNumber;
}

Base::~Base() {
    if (alive) --aliveNumber;
}

void Base::check_death() {
    if (!alive || health > 0) return;
    alive = false;
    --aliveNumber;
    const char* role = dynamic_cast<Fighter*>(this) ? "Fighter"
                     : dynamic_cast<Protector*>(this) ? "Protector" : "Caster";
    std::cout << role << ' ' << name << " is killed\n";
}

void Base::resolve_attack(Base* target, int multiplier, bool retaliates) {
    if (!alive || defensive) return;
    int damage = attack * multiplier;
    if (target->defensive) {
        damage = std::max(0, damage - target->attack);
        if (retaliates) health -= target->attack;
    }
    target->health -= damage;
    // Resolve both hits before announcing deaths, with the target first.
    target->check_death();
    check_death();
}

void Fighter::launch_attack(Base* target) {
    resolve_attack(target, dynamic_cast<Caster*>(target) ? 2 : 1, true);
}

void Protector::launch_attack(Base* target) {
    resolve_attack(target, dynamic_cast<Fighter*>(target) ? 2 : 1, true);
}

void Caster::launch_attack(Base* target) {
    resolve_attack(target, dynamic_cast<Protector*>(target) ? 2 : 1, false);
}
} // namespace final
