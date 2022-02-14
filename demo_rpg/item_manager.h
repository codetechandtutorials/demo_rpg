#pragma once
#include "item.h"

class ItemManager {
public:
  static Item* CreateArmor(std::string name, CoreStats cstats, ARMORSLOT slot) {
    Item* temp_item = new Item(new Armor(name, cstats, slot));
    return temp_item;
  }

  static Item* CreateWeapon(std::string name, CoreStats cstats, WEAPONSLOT slot, damagetype min, damagetype max, bool twohanded = false) {
    Item* temp_item = new Item(new Weapon(name, cstats, slot, min, max, twohanded));
    return temp_item;
  }

};
