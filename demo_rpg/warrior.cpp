#include "warrior.h"
#include "pc_macros.h"

Warrior::Warrior() : PlayerCharacterDelegate() {
  //MP = std::make_unique<PointWell>(BASEMP, BASEMP);  // be sure to init before PCCONSTRUCT MACRO
  PCCONSTRUCT

}
void Warrior::level_up() {
  LEVELUP
    if (GetLevel() == 2) {
      Abilities.emplace_back("PowerAttack", 4u, nullptr, 0u, 3u, ABILITYTARGET::ENEMY, ABILITYSCALER::STR);
    }
}