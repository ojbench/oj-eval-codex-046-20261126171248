"""Compare complete battle output with an independent integer-based model."""
import random
import subprocess
import sys

KINDS = ("Fighter", "Caster", "Protector")


def expected(rows):
    units = [list(row) + [False] for row in rows]
    output = []
    rounds = count = 0
    while sum(unit[2] > 0 for unit in units) > 1:
        rounds += 1
        for unit in units:
            if unit[2] <= 0:
                continue
            count = (count + 1) % 7
            unit[4] = count == 0
            if unit[4]:
                unit[2] += (3, 5, 7)[unit[0]]
                unit[3] += (2, 0, 1)[unit[0]]
        for i, attacker in enumerate(units):
            if attacker[2] <= 0 or attacker[4]:
                continue
            target = next((u for j, u in enumerate(units)
                           if i != j and u[2] > 0), None)
            if target is None:
                continue
            damage = attacker[3] * (2 if (attacker[0] + 1) % 3 == target[0] else 1)
            if target[4]:
                damage = max(0, damage - target[3])
                if attacker[0] != 1:
                    attacker[2] -= target[3]
            target[2] -= damage
            for unit in (target, attacker):
                if unit[2] <= 0:
                    output.append(f"{KINDS[unit[0]]} {unit[1]} is killed")
        assert rounds < 100000
    return "\n".join(output + [str(rounds)]) + "\n"


random.seed(1778)
for case in range(500):
    rows = [(random.randrange(3), f"unit{i}", random.randint(2, 1000),
             random.randint(2, 1000)) for i in range(random.randint(2, 40))]
    data = str(len(rows)) + "\n" + "".join(
        f"{KINDS[k]} {name} {h} {a}\n" for k, name, h, a in rows)
    result = subprocess.run([sys.argv[1]], input=data, text=True,
                            capture_output=True, check=True, timeout=5)
    assert result.stdout == expected(rows), (case, data, result.stdout, expected(rows))
print("500 randomized battle comparisons passed")
