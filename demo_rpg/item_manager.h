#pragma once
#include "types.h"
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

  // makes at least 1 potion
  static Item* CreatePotion(std::string name, welltype heal = 1u, itemcount qaunt = 1u, Buff* buff = nullptr) {
    Item* temp_item = new Item(new Potion(name, heal, (qaunt == 0) ? 1 : qaunt, buff));
    return temp_item;
  }

};
