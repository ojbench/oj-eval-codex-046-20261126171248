#include "Role.hpp"
#include <cassert>
#include <sstream>
#include <iostream>
#include <type_traits>

int main() {
    static_assert(std::is_abstract_v<final::Base>);
    static_assert(std::has_virtual_destructor_v<final::Base>);
    std::ostringstream output;
    auto* original = std::cout.rdbuf(output.rdbuf());
    {
        final::Fighter attacker("attacker", 10, 20);
        final::Caster defender("defender", 2, 10);
        defender.defend(true);
        attacker.launch_attack(&defender);
        assert(!attacker.isAlive() && !defender.isAlive());
        assert(final::Base::getAliveNumber() == 0);
        assert(output.str() == "Caster defender is killed\nFighter attacker is killed\n");
    }
    {
        final::Caster attacker("caster", 2, 2);
        final::Protector defender("protector", 2, 100);
        defender.defend(true);
        attacker.launch_attack(&defender);
        assert(attacker.isAlive() && defender.isAlive());
        assert(final::Base::getAliveNumber() == 2);
    }
    assert(final::Base::getAliveNumber() == 0);
    std::cout.rdbuf(original);
}
