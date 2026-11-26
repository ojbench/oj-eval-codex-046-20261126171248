#ifndef ROLE_HPP
#define ROLE_HPP

#include <string>
#include <algorithm>
#include <iostream>

namespace final {
class Fighter;
class Protector;
class Caster;

class Base {
    friend class Fighter;
    friend class Protector;
    friend class Caster;

private:
    std::string name;
    int health, attack;
    bool alive, defensive;
    inline static int aliveNumber = 0;

    void resolve_attack(Base* target, int multiplier, bool retaliates);
    void check_death();

public:
    Base(const std::string& name, int health, int attack);
    virtual ~Base();
    static int getAliveNumber() { return aliveNumber; }
    virtual void launch_attack(Base* target) = 0;
    virtual void defend(bool flag) = 0;
    bool isAlive() { return alive; }
    bool isDefensive() { return defensive; }
};

class Fighter : public Base {
public:
    Fighter(const std::string& name, int health, int attack)
        : Base(name, health, attack) {}
    void launch_attack(Base* target) override;
    void defend(bool flag) override {
        defensive = flag;
        if (flag) {
            health += 3;
            attack += 2;
        }
    }
};

class Protector : public Base {
public:
    Protector(const std::string& name, int health, int attack)
        : Base(name, health, attack) {}
    void launch_attack(Base* target) override;
    void defend(bool flag) override {
        defensive = flag;
        if (flag) {
            health += 7;
            attack += 1;
        }
    }
};

class Caster : public Base {
public:
    Caster(const std::string& name, int health, int attack)
        : Base(name, health, attack) {}
    void launch_attack(Base* target) override;
    void defend(bool flag) override {
        defensive = flag;
        if (flag) health += 5;
    }
};
inline Base::Base(const std::string& name, int health, int attack)
    : name(name), health(health), attack(attack), alive(true), defensive(false) {
    ++aliveNumber;
}

inline Base::~Base() {
    if (alive) --aliveNumber;
}

inline void Base::check_death() {
    if (!alive || health > 0) return;
    alive = false;
    --aliveNumber;
    const char* role = dynamic_cast<Fighter*>(this) ? "Fighter"
                     : dynamic_cast<Protector*>(this) ? "Protector" : "Caster";
    std::cout << role << ' ' << name << " is killed\n";
}

inline void Base::resolve_attack(Base* target, int multiplier, bool retaliates) {
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

inline void Fighter::launch_attack(Base* target) {
    resolve_attack(target, dynamic_cast<Caster*>(target) ? 2 : 1, true);
}

inline void Protector::launch_attack(Base* target) {
    resolve_attack(target, dynamic_cast<Fighter*>(target) ? 2 : 1, true);
}

inline void Caster::launch_attack(Base* target) {
    resolve_attack(target, dynamic_cast<Protector*>(target) ? 2 : 1, false);
}
} // namespace final
#endif
