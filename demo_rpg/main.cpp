#include <iostream>
#include "playercharacter.h"
int main() {

  // just test code for now, replace 'Warrior' with your class to test
  PlayerCharacter p1(new Warrior());



  {
    CoreStats plate_armor_stats;
    plate_armor_stats.Armor = 5;
    plate_armor_stats.ElementRes = 3;

    Armor* FullPlateMail = new Armor("Shiny Plate Armor", plate_armor_stats, ARMORSLOT::CHEST);
    if (p1.equip(FullPlateMail)) {
      std::cout << "equip success!\n";
    }
    else {
      std::cout << "equip failed!\n";
    }
  }

  {
    CoreStats leather_helm_stats;
    leather_helm_stats.Armor = 1;
    leather_helm_stats.ElementRes = 1;

    Armor* LeatherHelm = new Armor("Plain Leather Helmet", leather_helm_stats, ARMORSLOT::HELMET);
    if (p1.equip(LeatherHelm)) {
      std::cout << "equip success!\n";
    }
    else {
      std::cout << "equip failed!\n";
    }
  }

  {

    Weapon* LongSword = new Weapon("Long Sword", CoreStats(), WEAPONSLOT::MELEE, 3, 9);
    if (p1.equip(LongSword)) {
      std::cout << "equip success!\n";
    }
    else {
      std::cout << "equip failed!\n";
    }

  }



  for (int i = 0; i < 2; i++) {
    std::cout
      << p1.getClassName()
      << " Level " << p1.getLevel() << '\n'
      << "-EXP: " << p1.getCurrentEXP() << '/' << p1.getEXPToNextLevel() << '\n'
      << "-HP: " << p1.getCurrentHP() << '/' << p1.getMaxHP() << '\n'
      << "-MP: " << p1.getCurrentMP() << '/' << p1.getMaxMP() << '\n'
      << "-Stength: " << p1.getTotalStrength() << '\n'
      << "-Intellect: " << p1.getTotalIntellect() << '\n'
      << "-Agility: " << p1.getTotalAgility() << '\n'
      << "-Armor: " << p1.getTotalArmor() << '\n'
      << "-Resist: " << p1.getTotalElementRes() << '\n';

    auto AllBuffs = p1.getBuffList();
    std::cout << "-Buffs:\n";
    for (auto& buff : AllBuffs) {
      std::cout << "  -" << buff.Name << '\n';
    }

    auto AllAbilities = p1.getAbilityList();
    std::cout << "-Abilities:\n";
    for (auto& abil : AllAbilities) {
      std::cout << "  -" << abil.Name << '\n';
    }

    std::cout << "-Armor:\n";
    for (int i = 0; i < (int)ARMORSLOT::NUM_SLOTS; i++) {
      const Armor* tmp = dynamic_cast<Armor*>(p1.getEquippedArmorAt(i));

      if (tmp) {
        std::cout << " " << tmp->Name << ", A:(" << tmp->Stats.Armor << ") R:(" << tmp->Stats.Armor << ")\n";
      }
    }

    std::cout << "-Weapons:\n";
    for (int i = 0; i < (int)WEAPONSLOT::NUM_SLOTS; i++) {
      const Weapon* tmp = dynamic_cast<Weapon*>(p1.getEquippedWeaponAt(i));

      if (tmp) {
        std::cout << " " << tmp->Name << ", D:(" << tmp->MinDamage << "-" << tmp->MaxDamage << ")\n";
      }
    }





    if (i < 1) {
      p1.gainEXP(100u);
      Buff arm_buff("ThickSkin", 0, 0, 0, 2, 2);
      p1.applyBuff(arm_buff);
    }
  }

  return 0;
}