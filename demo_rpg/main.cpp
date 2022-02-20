#include <iostream>
#include "playercharacter.h"
#include "item_manager.h"

//int main() {
  // just test code for now, replace 'Warrior' with your class to test


  //Item* FullPlateMail = ItemManager::CreateArmor("Shiny Plate Armor", CoreStats(0, 0, 0, 5, 3), ARMORSLOT::CHEST);
  //Item* LeatherArmor = ItemManager::CreateArmor("Plain Leather Armor", CoreStats(0, 0, 0, 2, 1), ARMORSLOT::CHEST);
  //Item* LongSword = ItemManager::CreateWeapon("Long Sword", CoreStats(), WEAPONSLOT::MELEE, 3, 9);

  //ItemManager::Equip(FullPlateMail, &p1);
  //ItemManager::Equip(LeatherArmor, &p1);
  //ItemManager::Equip(LongSword, &p1);

  //

  //std::cout << "health before taking damage: " << p1.getCurrentHP() << '/' << p1.getMaxHP() << '\n';
  //p1.takeDamage(20);
  //std::cout << "health after taking damage: " << p1.getCurrentHP() << '/' << p1.getMaxHP() << '\n';
  //Item* HealPotion = ItemManager::CreatePotion("Minor Heal Potion", 3u, 3u);
  //ItemManager::MoveToBackpack(HealPotion, &p1);
  //ItemManager::Use(HealPotion, &p1);
  //std::cout << "health after using potion: " << p1.getCurrentHP() << '/' << p1.getMaxHP() << '\n';

  //ItemManager::MoveToBackpack(
  //  ItemManager::CreateWeapon("Rusty Hand Axe", CoreStats(), WEAPONSLOT::MELEE, 2, 4),
  //  &p1);

  //{
  //  auto inv = p1.getBackpackList();
  //  std::cout << "Inventory: ";
  //  for (auto it : inv) {
  //    std::cout << *it << ", ";
  //  }

  //  ItemManager::Use(HealPotion, &p1);
  //  ItemManager::Use(HealPotion, &p1);
  //}
  //std::cout << '\n';
  //std::cout << "health after using 2 potions: " << p1.getCurrentHP() << '/' << p1.getMaxHP() << '\n';

  //{
  //  auto inv = p1.getBackpackList();
  //  std::cout << "Inventory (after using potions): ";
  //  for (auto it : inv) {
  //    std::cout << *it << ", ";
  //  }
  //}

  //std::cout << "\n----END\n\n\n\n";

//  return 0;
//}