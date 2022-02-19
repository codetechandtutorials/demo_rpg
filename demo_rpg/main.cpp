#include <iostream>
#include "playercharacter.h"
#include "item_manager.h"

int main() {
  // just test code for now, replace 'Warrior' with your class to test
  PlayerCharacter p1(new Warrior());

  Item* FullPlateMail = ItemManager::CreateArmor("Shiny Plate Armor", CoreStats(0, 0, 0, 5, 3), ARMORSLOT::CHEST);
  Item* LeatherArmor = ItemManager::CreateArmor("Plain Leather Armor", CoreStats(0, 0, 0, 2, 1), ARMORSLOT::CHEST);
  Item* LongSword = ItemManager::CreateWeapon("Long Sword", CoreStats(), WEAPONSLOT::MELEE, 3, 9);

  ItemManager::Equip(FullPlateMail, &p1);
  ItemManager::Equip(LeatherArmor, &p1);
  ItemManager::Equip(LongSword, &p1);

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

  std::cout << "health before taking damage: " << p1.getCurrentHP() << '/' << p1.getMaxHP() << '\n';
  p1.takeDamage(20);
  std::cout << "health after taking damage: " << p1.getCurrentHP() << '/' << p1.getMaxHP() << '\n';
  Item* HealPotion = ItemManager::CreatePotion("Minor Heal Potion", 3u, 3u);
  ItemManager::MoveToBackpack(HealPotion, &p1);
  ItemManager::Use(HealPotion, &p1);
  std::cout << "health after using potion: " << p1.getCurrentHP() << '/' << p1.getMaxHP() << '\n';

  ItemManager::MoveToBackpack(
    ItemManager::CreateWeapon("Rusty Hand Axe", CoreStats(), WEAPONSLOT::MELEE, 2, 4),
    &p1);

  {
    auto inv = p1.getBackpackList();
    std::cout << "Inventory: ";
    for (auto it : inv) {
      std::cout << *it << ", ";
    }

    ItemManager::Use(HealPotion, &p1);
    ItemManager::Use(HealPotion, &p1);
  }
  std::cout << '\n';
  std::cout << "health after using 2 potions: " << p1.getCurrentHP() << '/' << p1.getMaxHP() << '\n';

  {
    auto inv = p1.getBackpackList();
    std::cout << "Inventory (after using potions): ";
    for (auto it : inv) {
      std::cout << *it << ", ";
    }
  }

  std::cout << "\n----END\n\n\n\n";

  return 0;
}