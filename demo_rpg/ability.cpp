#include "ability.h"


Ability::Ability(std::string name, uint32_t hpe, Buff* b, uint32_t cost, uint32_t cd, ABILITYTARGET t, ABILITYSCALER s)
  : Name(name), HpEffect(hpe), GivenBuff(b), Cost(cost), Cooldown(cd), Target(t), Scaler(s) {
  CooldownLeft = 0u;
}

Ability::~Ability() {
  if (GivenBuff) {
    delete GivenBuff;
    GivenBuff = nullptr;
  }
}

const std::string Ability::GetName() const noexcept {
  return Name;
}

const uint32_t Ability::GetCooldown() const noexcept {
  return Cooldown;
}

const uint32_t Ability::GetHPEffect() const noexcept {
  return HpEffect;
}

const Buff* Ability::GetBuff() const noexcept {
  return GivenBuff;
}

const uint32_t Ability::GetCost() const noexcept {
  return Cost;
}

const ABILITYTARGET Ability::GetTarget() const noexcept {
  return Target;
}

const ABILITYSCALER Ability::GetScaler() const noexcept {
    return Scaler;
}
