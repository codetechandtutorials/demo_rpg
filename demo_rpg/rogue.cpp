#include "rogue.h"
#include "pc_macros.h"

Rogue::Rogue() : PlayerCharacterDelegate() {
  //MP = std::make_unique<PointWell>(BASEMP, BASEMP);  // be sure to init before PCCONSTRUCT MACRO
  PCCONSTRUCT;

}
void Rogue::level_up() noexcept {
  LEVELUP;
  if (GetLevel() == 2) {
    Abilities.emplace_back(new Ability("PreciseAttack", 6u, nullptr, 0u, 3u, ABILITYTARGET::ENEMY, ABILITYSCALER::AGI));
  }
}