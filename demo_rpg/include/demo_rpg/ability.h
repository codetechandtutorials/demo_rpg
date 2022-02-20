#pragma once
#include <cstdint>
#include <string>

enum class ABILITYTARGET { SELF, ALLY, ENEMY };
enum class ABILITYSCALER { NONE, STR, AGI, INT };

struct Ability {
  Ability(std::string name, uint32_t cost, uint32_t cd, ABILITYTARGET t, uint32_t hpe, ABILITYSCALER s) : 
    Name(name), Cost(cost), Cooldown(cd), Target(t), HpEffect(hpe), Scaler(s) {}

  std::string Name = "unnamed";
  uint32_t Cost = 0;  // assume mp if there is a cost
  uint32_t Cooldown = 1;  // number of rounds you have to wait before using it again
  ABILITYTARGET Target = ABILITYTARGET::SELF;
  uint32_t HpEffect = 1;
  ABILITYSCALER Scaler = ABILITYSCALER::NONE;
};