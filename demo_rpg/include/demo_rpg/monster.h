#pragma once
#include "types.h"
#include "pointwell.h"
#include <memory>
class Monster {
public:
  Monster(welltype hp, damagetype min, damagetype max);
  PointWell HP;
  [[nodiscard]] const damagetype Attack() const;
  [[nodiscard]] const damagetype GetMinDamage() const noexcept;
  [[nodiscard]] const damagetype GetMaxDamage() const noexcept;
private:
  damagetype MinDamage, MaxDamage;
  Monster() = delete;
  Monster(const Monster&) = delete;
  Monster(const Monster&&) = delete;
};

