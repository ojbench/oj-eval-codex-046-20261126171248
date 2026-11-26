#ifndef ROLE_HPP
#define ROLE_HPP

#include <string>

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
    static int aliveNumber;

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
} // namespace final
#endif
