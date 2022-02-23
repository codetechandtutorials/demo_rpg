#include "ability.h"


Ability::Ability(std::string name, uint32_t hpe, Buff* b, uint32_t cost, uint32_t cd, ABILITYTARGET t, ABILITYSCALER s)
  : Name(name), HpEffect(hpe), GivenBuff(b), Cost(cost), Cooldown(cd), Target(t), Scaler(s) {
}

Ability::~Ability() {
  if (GivenBuff) {
    delete GivenBuff;
    GivenBuff = nullptr;
  }
}