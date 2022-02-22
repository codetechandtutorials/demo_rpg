#pragma once
#include <cstdint>
#include <string>
#include "buff.h"

enum class ABILITYTARGET { SELF, ALLY, ENEMY };
enum class ABILITYSCALER { NONE, STR, AGI, INT };

struct Ability {

  Ability(std::string name = "unnamed",
    uint32_t hpe = 1u,
    Buff* b = nullptr,
    uint32_t cost = 0u,
    uint32_t cd = 1u,
    ABILITYTARGET t = ABILITYTARGET::SELF,
    ABILITYSCALER s = ABILITYSCALER::NONE);

  ~Ability();

  std::string Name;
  uint32_t HpEffect;
  Buff* GivenBuff;
  uint32_t Cost;      // assume mp if there is a cost
  uint32_t Cooldown;  // number of rounds you have to wait before using it again
  ABILITYTARGET Target;
  ABILITYSCALER Scaler;
};