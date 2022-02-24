#include "monster.h"
#include "random.h"

Monster::Monster(welltype hp, damagetype min, damagetype max)
  : HP(hp, hp), MinDamage(min), MaxDamage(max) {
}

const damagetype Monster::Attack() const {
  return Random::NTK(MinDamage, MaxDamage);
}

const damagetype Monster::GetMinDamage() const noexcept {
  return MinDamage;
}

const damagetype Monster::GetMaxDamage() const noexcept {
  return MaxDamage;
}
