#include "wizard.h"
#include "pc_macros.h"

Wizard::Wizard() : PlayerCharacterDelegate() {
  MP = std::make_unique<PointWell>(BASEMP, BASEMP);  // be sure to init before PCCONSTRUCT MACRO
  PCCONSTRUCT
    Abilities.emplace_back("Firebolt", 4u, nullptr, 2u, 1u, ABILITYTARGET::ENEMY, ABILITYSCALER::INT);
}
void Wizard::level_up() {
  LEVELUP
    if (CurrentLevel == 2) {
      Abilities.emplace_back("IceBolt", 6u, nullptr, 3u, 1u, ABILITYTARGET::ENEMY, ABILITYSCALER::INT);
      increaseStats(0, 1);
    }
}