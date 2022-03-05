#include "wizard.h"
#include "pc_macros.h"

Wizard::Wizard() : PlayerCharacterDelegate() {
  MP = std::make_unique<PointWell>(BASEMP, BASEMP);  // be sure to init before PCCONSTRUCT MACRO
  PCCONSTRUCT;
  Abilities.emplace_back(new Ability("Firebolt", 4u, nullptr, 2u, 1u, ABILITYTARGET::ENEMY, ABILITYSCALER::INT));
}
void Wizard::level_up() noexcept {
  LEVELUP;
  if (GetLevel() == 2) {
    Abilities.emplace_back(new Ability("IceBolt", 6u, nullptr, 3u, 1u, ABILITYTARGET::ENEMY, ABILITYSCALER::INT));
    increase_stats(0, 1);
  }
}