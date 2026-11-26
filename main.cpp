#include "Role.hpp"

#include <iostream>
#include <memory>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    if (!(std::cin >> n)) return 0;
    std::vector<std::unique_ptr<final::Base>> roles;
    for (int i = 0; i < n; ++i) {
        std::string role, name;
        int health, attack;
        std::cin >> role >> name >> health >> attack;
        if (role == "Fighter")
            roles.push_back(std::make_unique<final::Fighter>(name, health, attack));
        else if (role == "Protector")
            roles.push_back(std::make_unique<final::Protector>(name, health, attack));
        else
            roles.push_back(std::make_unique<final::Caster>(name, health, attack));
    }

    int round = 0, count = 0;
    while (final::Base::getAliveNumber() > 1) {
        ++round;
        for (auto& role : roles) {
            if (!role->isAlive()) continue;
            ++count;
            role->defend(count == 7);
            if (count == 7) count = 0;
        }
        for (auto& role : roles) {
            if (!role->isAlive() || role->isDefensive()) continue;
            for (auto& target : roles) {
                if (target != role && target->isAlive()) {
                    role->launch_attack(target.get());
                    break;
                }
            }
        }
    }
    std::cout << round << '\n';
}
